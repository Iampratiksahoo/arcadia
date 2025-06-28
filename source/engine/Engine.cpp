#include "Engine.h"

#include "Core.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_ASPECT_RATIO ((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT)
#define WINDOW_TITLE "Arcadia"

#define OPENGL_VERSION_MAJOR 3
#define OPENGL_VERSION_MINOR 3

#define FIXED_DELTA_TIME 1.f/120.f

Engine::Engine(AbstractGameBase* game) : 
m_game(game),
m_window(nullptr), 
m_fixedDeltaTimeAccum(0.0f), 
m_lastFrameTime(0.0f),       
m_deltaTime(0.0f)            
{
    // set the width and height 
    m_width = WINDOW_WIDTH;
    m_height = WINDOW_HEIGHT;
    m_title = WINDOW_TITLE;

    // set the screen width and height for the game 
    m_game->m_windowWidth = m_width; 
    m_game->m_windowHeight = m_height;

    // first initialize GLFW to use OpenGL
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    // glfwWindowHint(GLFW_RESIZABLE, false);

    try
    {
        // create a window 
        if (m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr)) 
        {
            AC_LOG("Engine::Ctor() Window initialized"); 

            // set the user pointer for later usage
            glfwSetWindowUserPointer( m_window, this );

            // set the current glfw context for the window.
            glfwMakeContextCurrent(m_window);

            if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
            {
                AC_LOG("Engine::Ctor() Loaded GLAD successfully"); 

                // set the callback for key input
                glfwSetKeyCallback(m_window, keyCallback);

                // set callback for mouse input 
                glfwSetCursorPosCallback(m_window, cursorPositionCallback);

                // set callback for when the mouse enters the screen 
                glfwSetCursorEnterCallback(m_window, cursorEnterCallback);

                // set callback for when mouse is clicked 
                glfwSetMouseButtonCallback(m_window, mouseButtonCallback);

                // set callback for when the window size is changed
                glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);

                // OpenGL configuration
                // --------------------
                glfwGetFramebufferSize(m_window, &m_width, &m_height);
                glViewport(0, 0, m_width, m_height);
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                // ok now everything is setup, we can initialize the game
                m_game->Init();

                // once the game has been initialize, we officially start the game 
                SceneManager::gameStart(); 
            }
            else
            {
                throw std::runtime_error("Failed to load GLAD");
            }
        }
        else
        {
            throw std::runtime_error("Failed to create window");
        }
    }
    catch (std::exception e)
    {
        AC_ERROR("Engine::Ctor() Failed to create window with error: %s", e.what());   
        glfwTerminate();
        exit(-1);
    }

    // master while loop 
    while(!glfwWindowShouldClose(m_window))
    {
        // calculate the delta time
        float currentFrame = glfwGetTime();
        m_deltaTime = currentFrame - m_lastFrameTime;
        m_lastFrameTime = currentFrame;

        // accumulate the fixed delta time 
        m_fixedDeltaTimeAccum += m_deltaTime; 
        m_fixedDeltaTimeAccum = Math::Min( m_fixedDeltaTimeAccum,  0.25f); // avoid sprial of death 

        // call the Input class's BeginFrame to track the key states
        Input::beginFrame();

        // poll glfw window events
        glfwPollEvents();

        // update the game state
        SceneManager::update( m_deltaTime ); 

        while (m_fixedDeltaTimeAccum >= FIXED_DELTA_TIME )
        {
            SceneManager::fixedUpdate( FIXED_DELTA_TIME );
            m_fixedDeltaTimeAccum -= FIXED_DELTA_TIME; 
        }

        // clear the scree
        clearScreen();

        // Ask the scene manager to render all scenes 
        SceneManager::render();

        // finally, swap buffers and poll events
        glfwSwapBuffers( m_window );
    }

    // once the game is done running, preform a cleanup 
    // this needs to happen here, before the destructor kicks in 
    m_game->Cleanup();
    SceneManager::cleanup();
}

Engine::~Engine()
{
    // clear all the resources
    ResourceManager::Clear();

    // if we have a valid window then terminate it
    if( m_window )
    {
        glfwDestroyWindow( m_window );
        glfwTerminate();
    }
}

void Engine::clearScreen()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Engine::framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    if (Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window)))
    {
        engine->m_width = width;
        engine->m_height = height;
    }

    // You need to get the Game instance from the window user pointer if you want to update members.
    glViewport(0, 0, width, height);
}

void Engine::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{ 
    // now record states of each key press 
    Input::updateKey(key, action);
}

void Engine::cursorPositionCallback(GLFWwindow *window, double xpos, double ypos)
{
    Input::updateMousePos(xpos, ypos);
}

void Engine::cursorEnterCallback(GLFWwindow *window, int entered)
{
    Input::m_mouseInsideWindow = entered;
}

void Engine::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
    // now record states of each key press, we use the same one for mouse as well.
    Input::updateKey(button, action);
}
