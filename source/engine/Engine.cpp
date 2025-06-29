#include "Engine.h"

#include "Core.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "AbstractSystemManager.h"

#define OPENGL_VERSION_MAJOR 3
#define OPENGL_VERSION_MINOR 3

Engine::Engine(AbstractGameBase* game) : 
m_game(game),
m_window(nullptr), 
m_fixedDeltaTimeAccum(0.0f), 
m_lastFrameTime(0.0f),       
m_deltaTime(0.0f)            
{
    // first try to load the ini file 
    std::string iniPathStr = FileHandler::GetAbsolutePath( m_game->GetIniPath() );
    const char* iniPath = iniPathStr.c_str(); 
    IniParser gameIni( iniPath );

    // if there is no ini file, then create a default one and kill the engine 
    if(!gameIni.Load())
    {
        AC_WARN("Engine::Ctor() No Ini file found for the game, creating one now at '%s'", iniPath);

        gameIni.Write("Window", "iWidth", "800");
        gameIni.Write("Window", "iHeight", "600");
        gameIni.Write("Window", "sTitle", "New Game");
        gameIni.Write("Window", "bResizable", "0");

        gameIni.Write("Physics", "fFixedDeltaTime", "0.008333333");

        gameIni.Save();

        AC_WARN("Ini file created, kindly configure it and retry");
        exit(-1);
    }

    // parse the loaded ini file data
    m_width = std::stof( gameIni.Read("Window", "iWidth", "800") );
    m_height = std::stof( gameIni.Read("Window", "iHeight", "600") );
    std::string titleStr = gameIni.Read("Window", "sTitle", "New Game");
    m_title = titleStr.c_str();
    m_resizable =  std::stoi( gameIni.Read("Window", "bResizable", "1") );

    m_fixedDeltaTime = std::stof( gameIni.Read("Physics", "fFixedDeltaTime", "0.008333333") );

    // set the screen width and height for the game 
    m_game->m_windowWidth = m_width; 
    m_game->m_windowHeight = m_height;

    // add all the systems managers 
    addSystemManagers();

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
                // so call gameStart for all the systemManagers as well.
                for(AbstractSystemManager* manager : m_systemManagers)
                {
                    manager->gameStart();
                }
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

        // update all the systems manager 
        for(AbstractSystemManager* manager : m_systemManagers)
        {
            manager->update( m_deltaTime );
        }

        while (m_fixedDeltaTimeAccum >= m_fixedDeltaTime )
        {
            // send fixed update to all the systems managers 
            for(AbstractSystemManager* manager : m_systemManagers)
            {
                manager->fixedUpdate( m_fixedDeltaTime );
            }
            m_fixedDeltaTimeAccum -= m_fixedDeltaTime; 
        }

        // clear the scree
        clearScreen();

        // Ask the system manager to render all 
        for(AbstractSystemManager* manager : m_systemManagers)
        {
            manager->render();
        }

        // finally, swap buffers and poll events
        glfwSwapBuffers( m_window );
    }

    // once the game is done running, preform a cleanup 
    // this needs to happen here, before the destructor kicks in 
    m_game->Cleanup();

    // now cleanup the engine system managers 
    for(AbstractSystemManager* manager : m_systemManagers)
    {
        manager->cleanup();
    }
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

void Engine::addSystemManagers()
{
    m_systemManagers.push_back( static_cast<AbstractSystemManager*>(SceneManager::GetInstance()));
    m_systemManagers.push_back( static_cast<AbstractSystemManager*>(CollisionManager::GetInstance()));
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
