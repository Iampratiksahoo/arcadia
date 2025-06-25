#include "Breakout.h"
#include "GameLevel.h"
#include "Ball.h"
#include "Brick.h"

Breakout::Breakout()
{
    m_paddleSize = Vector2<float>(100.f, 20.f);
    m_paddleVelocity = 500.f; 

    m_ballRadius = 10.f; 
    m_ballVelocity = 350.f;
}

Breakout::~Breakout()
{
}

// Initialize the game
void Breakout::Init()
{
    int windowWidth = getWindowWidth();
    int windowHeight = getWindowHeight();

    // load the required resources 
    ResourceManager::LoadShader("core", "resources/shaders/default.vert", "resources/shaders/default.frag");
    ResourceManager::LoadTexture2D("bg", "resources/breakout/sprites/background.jpg", false);
    ResourceManager::LoadTexture2D("block", "resources/breakout/sprites/block.png", false);
    ResourceManager::LoadTexture2D("block_soild", "resources/breakout/sprites/block_solid.png", false);
    ResourceManager::LoadTexture2D("paddle", "resources/breakout/sprites/paddle.png", true);
    ResourceManager::LoadTexture2D("ball", "resources/breakout/sprites/ball.png", true);

    // create a camera to render stuff
    Camera2D camera(
        0.0f, 
        static_cast<float>(windowWidth), 
        static_cast<float>(windowHeight), 
        0.0f, 
        -1.0f, 
        1.0f
    );

    ResourceManager::GetShader("core").Use().SetInteger("image", 0);
    ResourceManager::GetShader("core").SetMatrix4("projection", camera.GetProjectionMatrix());

    // load the levels 
    GameLevel* one = new GameLevel();      
    one->Load("resources/breakout/level/level_001.level", windowWidth, windowHeight / 2);

    GameLevel* two = new GameLevel();      
    two->Load("resources/breakout/level/level_002.level", windowWidth, windowHeight / 2);

    GameLevel* three = new GameLevel();    
    three->Load("resources/breakout/level/level_003.level", windowWidth, windowHeight / 2);

    GameLevel* four = new GameLevel();     
    four->Load("resources/breakout/level/level_004.level", windowWidth, windowHeight / 2);

    GameLevel* five = new GameLevel();     
    five->Load("resources/breakout/level/level_005.level", windowWidth, windowHeight / 2);


    m_levels.push_back(one);
    m_levels.push_back(two);
    m_levels.push_back(three);
    m_levels.push_back(four);
    m_levels.push_back(five);

    m_currentLevel = 2;

    // construct the bg gameObject
    m_background = new GameObject();
    m_background->transform->SetPosition( Vector3<float>::Zero );

    SpriteRenderer* renderer = m_background->AddComponent<SpriteRenderer>();
    renderer->shader = &ResourceManager::GetShader("core");
    renderer->texture = &ResourceManager::GetTexture2D("bg");
    renderer->SetSize(windowWidth, windowHeight);

    // now construct the paddle gameObject 
    m_paddle = new GameObject(); 
    m_paddle->transform->SetPosition( Vector3<float>(
        windowWidth / 2.f - m_paddleSize.x / 2.f, 
        windowHeight - m_paddleSize.y, 
        0.f
    ) ); 

    SpriteRenderer* paddleRenderer = m_paddle->AddComponent<SpriteRenderer>();
    paddleRenderer->shader = &ResourceManager::GetShader("core");
    paddleRenderer->texture = &ResourceManager::GetTexture2D("paddle");
    paddleRenderer->SetSize( m_paddleSize );

    // now add the ball 
    m_ball = new GameObject(); 

    Vector3<float> ballPos (
        m_paddle->transform->GetPosition().x + (m_paddleSize.x / 2.f) - m_ballRadius , 
        m_paddle->transform->GetPosition().y - (m_ballRadius * 2),
        0.f
    );

    m_ball->transform->SetPosition( ballPos );

    SpriteRenderer* ballRenderer = m_ball->AddComponent<SpriteRenderer>();
    ballRenderer->shader = &ResourceManager::GetShader("core");
    ballRenderer->texture = &ResourceManager::GetTexture2D("ball");

    // now add the ball component 
    Ball* ball = m_ball->AddComponent<Ball>(); 
    ball->SetGameInstance(this);
    ball->SetRadius(m_ballRadius);
    ball->isStuck = true;

    m_ball->transform->SetParent( m_paddle->transform );
}

// Update the game state
void Breakout::Update(float deltaTime)
{
    int windowWidth = getWindowWidth();
    Vector3<float> translation;
    
    if(Input::GetKey(KeyCode::A)
        && m_paddle->transform->GetPosition().x > 0 )
    {
        translation = Vector3<float>( -m_paddleVelocity, 0.f, 0.f) * deltaTime ;
    }
    if(Input::GetKey(KeyCode::D)
        && m_paddle->transform->GetPosition().x < windowWidth - m_paddleSize.x)
    {
        translation = Vector3<float>( m_paddleVelocity, 0.f, 0.f) * deltaTime ;
    }
    if(Input::GetKeyDown(KeyCode::SPACE))
    {
        if(m_ball->transform->GetParent() != nullptr)
        {
            m_ball->transform->SetParent(nullptr);
            m_ball->GetComponent<Ball>()->isStuck = false;
        }
    }
    
    m_paddle->transform->Translate( translation );

    m_ball->GetComponent<Ball>()->Move(
        deltaTime, 
        m_ballVelocity, 
        windowWidth, 
        getWindowHeight()
    );
}

// Render the game
void Breakout::Render()
{
    // first draw the background 
    m_background->Render();

    // then draw the level bricks 
    GetCurrentLevel()->Render();

    // now render the ball 
    m_ball->Render();

    // now render the paddle 
    m_paddle->Render();
}

// Clean up resources
void Breakout::Cleanup()
{
    for(GameLevel* level : m_levels)
    {
        delete level; 
    }

    delete m_background; 
    delete m_paddle; 
    delete m_ball; 
}

GameLevel *Breakout::GetCurrentLevel() const
{
    return m_levels[m_currentLevel - 1];
}