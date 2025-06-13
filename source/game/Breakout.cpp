#include "Breakout.h"

Breakout::Breakout() :
    m_gameObject(nullptr),
    m_width(WINDOW_WIDTH), 
    m_height(WINDOW_HEIGHT)
{

}

Breakout::~Breakout()
{
    if(m_gameObject != nullptr)
    {
        delete m_gameObject;
    }
}

// Initialize the game
void Breakout::Init()
{
    m_gameObject = new GameObject();
    m_gameObject->transform->position = Vector3<float>(200.f);
    m_gameObject->transform->rotation = Vector3<float>::Zero;
}

// Handle input events
void Breakout::ProcessInput(float deltaTime)
{

}

// Update the game state
void Breakout::Update(float deltaTime)
{
    if(Input::GetKeyDown(KeyCode::SPACE))
    {
        if( !m_gameObject->HasComponent<SpriteRenderer>() )
        {
            m_gameObject->AddComponent<SpriteRenderer>();
            AC_NOTICE("Breakout::Added SpriteRenderComponent to the gameObject");
        }
        else if ( !m_gameObject->GetComponent<SpriteRenderer>()->shader )
        {
            Shader* shader = &ResourceManager::LoadShader("default", "shaders/default.vert", "shaders/default.frag"); 
            Camera2D* camera = new Camera2D(
                0.f, 
                m_width, 
                m_height, 
                0.f, 
                -1.f, 
                1.f
            );
            shader->Use()->SetInteger("image", 0);
            shader->SetMatrix4("projection", camera->GetProjectionMatrix());
            m_gameObject->GetComponent<SpriteRenderer>()->shader = shader;
            AC_NOTICE("Breakout::Added a Shader to the gameObject's SpriteRenderer");
        }
        else if( !m_gameObject->GetComponent<SpriteRenderer>()->texture )
        {
            m_gameObject->GetComponent<SpriteRenderer>()->texture = &ResourceManager::LoadTexture2D("face", "resources/sprites/face.png", true );
            // m_gameObject->GetComponent<SpriteRenderer>()->SetSize(300.f, 400.f);
            AC_NOTICE("Breakout::Added a Texture2D to the gameObject's SpriteRenderer wiwth size: %s", m_gameObject->GetComponent<SpriteRenderer>()->GetSize().ToString());
        }
    }

    float speed = 100.f;
    if(Input::GetKey(KeyCode::W))
    {
        m_gameObject->transform->Translate(Vector3<float>(0.f, -speed * deltaTime, 0));
    }
    if(Input::GetKey(KeyCode::S))
    {
        m_gameObject->transform->Translate(Vector3<float>(0.f, speed * deltaTime, 0));
    }
    if(Input::GetKey(KeyCode::A))
    {
        m_gameObject->transform->Translate(Vector3<float>(-speed * deltaTime, 0.f, 0));
    }
    if(Input::GetKey(KeyCode::D))
    {
        m_gameObject->transform->Translate(Vector3<float>(speed * deltaTime, 0.f, 0));
    }
}

// Render the game
void Breakout::Render()
{
    m_gameObject->Draw();
}

// Clean up resources
void Breakout::Cleanup()
{
}