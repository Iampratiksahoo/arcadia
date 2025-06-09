#include "Breakout.h"

Breakout::Breakout() :
    m_renderer(nullptr),
    m_width(WINDOW_WIDTH), 
    m_height(WINDOW_HEIGHT)
{

}

Breakout::~Breakout()
{
    if(m_renderer != nullptr)
    {
        delete m_renderer;
    }
}

// Initialize the game
void Breakout::Init()
{
    // load the resources
    ResourceManager::LoadShader("core", "shaders/default.vert", "shaders/default.frag");
    ResourceManager::LoadTexture2D("face" , "resources/sprites/face.png", true);
    
    // configure shaders
    Camera2D* camera = new Camera2D(
        0.0f, 
        static_cast<float>(m_width), 
        static_cast<float>(m_height),
        0.f, 
        -1.0f, 
        1.0f
    );

    Shader *shader = new Shader( ResourceManager::GetShader("core") );
    shader->Use().SetInteger("image", 0);
    shader->SetMatrix4("projection", camera->GetProjectionMatrix());
    
    // set render-specific controls]
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
            Vector2<float>(300.f, 400.f), 
            45.f, 
            Vector3<float>(1.f)
        );
    }
}

// Clean up resources
void Breakout::Cleanup()
{

}