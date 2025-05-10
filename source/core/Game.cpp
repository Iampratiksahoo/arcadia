#include "Game.h"

#include "Core.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

Game::Game() : 
m_state(State::None), 
m_window(nullptr),
m_width(WINDOW_WIDTH), 
m_height(WINDOW_HEIGHT),
m_title(WINDOW_TITLE)
{
    // initialize the glfw and other stuff 
    Init();

    // master while loop 
    while(!glfwWindowShouldClose(m_window))
    {
        // calculate the delta time
        float currentFrame = glfwGetTime();
        m_deltaTime = currentFrame - m_lastFrameTime;
        m_lastFrameTime = currentFrame;

        // process input
        ProcessInput( m_deltaTime );

        // update the game state
        Update( m_deltaTime );

        // render the game
        Render();

        // finally, swap buffers and poll events
        glfwSwapBuffers( m_window );
        glfwPollEvents();
    }
}

Game::~Game()
{
    if( m_window )
    {
        glfwDestroyWindow( m_window );
        glfwTerminate();
    }
}

void Game::Init()
{
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

    try
    {
        // create a window 
        if (m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr)) 
        {
            AC_LOG("Window initialized"); 
            glfwMakeContextCurrent(m_window);
            if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
            {
                AC_LOG("Loaded GLAD successfully"); 
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
}

void Game::ProcessInput(float deltaTime)
{
}

void Game::Update(float deltaTime)
{
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Game::Render()
{
}