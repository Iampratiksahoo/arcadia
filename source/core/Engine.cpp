#include "Engine.h"

#include "Core.h"
#include "SpriteRenderer.h"
#include "Shader.h"
#include "ResourceManager.h"
#include "IGame.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Engine::Engine(IGame& game) : 
m_game(game),
m_state(State::None), 
m_window(nullptr),
m_width(WINDOW_WIDTH), 
m_height(WINDOW_HEIGHT),
m_title(WINDOW_TITLE)
{
    // initialize the glfw and other stuff 
    // initialize the keys array to false
    for (int i = 0; i < 1024; i++)
    {
        m_keys[i] = false;
    }

    // first initialize GLFW to use OpenGL
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, false);

    try
    {
        // create a window 
        if (m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr)) 
        {
            AC_LOG("Window initialized"); 

            // set the current glfw context for the window.
            glfwMakeContextCurrent(m_window);

            if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
            {
                AC_LOG("Loaded GLAD successfully"); 

                // set the callback for key input
                glfwSetKeyCallback(m_window, keyCallback);
                glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);

                // OpenGL configuration
                // --------------------
                glViewport(0, 0, m_width, m_height);
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                // ok now everything is setup, we can initialize the game
                m_game.Init();
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
        AC_ERROR("Failed to create window with error: %s", e.what());   
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

        // poll glfw window events
        glfwPollEvents();

        // process input
        m_game.ProcessInput( m_deltaTime );

        // update the game state
        m_game.Update( m_deltaTime );

        // clear the scree
        ClearScreen();

        // render the game
        m_game.Render();

        // finally, swap buffers and poll events
        glfwSwapBuffers( m_window );
    }

    // once the game is done running, preform a cleanup 
    // this needs to happen here, before the destructor kicks in 
    m_game.Cleanup();
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

void Engine::ClearScreen()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Engine::framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.

    // You need to get the Game instance from the window user pointer if you want to update members.
    glViewport(0, 0, width, height);
}

void Engine::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    // if (key >= 0 && key < 1024)
    // {
    //     if (action == GLFW_PRESS)
    //         m_keys[key] = true;
    //     else if (action == GLFW_RELEASE)
    //         m_keys[key] = false;
    // }
}
