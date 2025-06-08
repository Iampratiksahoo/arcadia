#include "Breakout.h"

#include "../core/ResourceManager.h"
#include "../core/Core.h"
#include "../core/SpriteRenderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Initialize the game
void Breakout::Init()
{
    // load the resources
    ResourceManager::LoadShader("core", "shaders/core_vertex.glsl", "shaders/core_fragment.glsl");
    ResourceManager::LoadTexture2D("face" , "resources/sprites/face.png", true);

    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(WINDOW_WIDTH), 
                                        static_cast<float>(WINDOW_HEIGHT),
                                        0.f, -1.0f, 1.0f);
    

    Shader shader = ResourceManager::GetShader("core");
    shader.Use().SetInt("image", 0);
    shader.SetMat4("projection", projection);

    // set render-specific controls
    m_renderer = new SpriteRenderer(shader);
}

// Handle input events
void Breakout::ProcessInput(float deltaTime)
{

}

// Update the game state
void Breakout::Update(float deltaTime)
{

}

// Render the game
void Breakout::Render()
{
    if(m_renderer != nullptr)
    {
        Texture2D faceTexture = ResourceManager::GetTexture2D("face");
        m_renderer->DrawSprite(
            faceTexture,
            Vector2<float>(200.f), 
            Vector2<float>(300.f), 
            0.f, 
            Vector3<float>(.0f, 1.0f, .0f)
        );
    }
}

// Clean up resources
void Breakout::Cleanup()
{

}