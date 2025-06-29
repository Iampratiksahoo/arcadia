#include "Breakout.h"
#include "GameLevel.h"
#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"

Breakout::Breakout()
{
    m_paddleSize = Vector2<float>(100.f, 20.f);

    m_ballRadius = 10.f; 
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

    SetCurrentLevel(2);

    AC_NOTICE("Breakout::Init() Creating Background Object");

    // construct the bg gameObject
    m_background = new GameObject();
    m_background->name = "Breakout BG";
    m_background->transform->SetPosition( Vector3<float>::Zero );

    SpriteRenderer* renderer = m_background->AddComponent<SpriteRenderer>();
    renderer->shader = &ResourceManager::GetShader("core");
    renderer->texture = &ResourceManager::GetTexture2D("bg");
    renderer->SetSize(windowWidth, windowHeight);

    AC_NOTICE("Breakout::Init() Creating Paddle Object");

    // now construct the paddle gameObject 
    m_paddle = new GameObject(); 
    m_paddle->name = "Paddle";
    m_paddle->transform->SetPosition( Vector3<float>(
        windowWidth / 2.f - m_paddleSize.x / 2.f, 
        windowHeight - m_paddleSize.y, 
        0.f
    ) ); 

    SpriteRenderer* paddleRenderer = m_paddle->AddComponent<SpriteRenderer>();
    paddleRenderer->shader = &ResourceManager::GetShader("core");
    paddleRenderer->texture = &ResourceManager::GetTexture2D("paddle");
    paddleRenderer->SetSize( m_paddleSize );

    Paddle* paddle = m_paddle->AddComponent<Paddle>();
    paddle->SetGameInstance( this );
    paddle->size = m_paddleSize; 

    BoxCollider2D* boxCollider = m_paddle->AddComponent<BoxCollider2D>();
    boxCollider->size = m_paddleSize; 
    

    AC_NOTICE("Breakout::Init() Creating Ball Object");

    // now add the ball 
    m_ball = new GameObject(); 
    m_ball->name = "Ball";

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

    // now add a circle collider to the ball 
    CircleCollider2D* circleCollider = m_ball->AddComponent<CircleCollider2D>();
    circleCollider->radius = m_ballRadius; 

    AC_NOTICE("Breakout::Init() Setting the ball's parent to be the paddle");

    if (!m_ball || !m_ball->transform) {
    AC_ERROR("Breakout::Init() m_ball or its transform is NULL!");
    }

    if (!m_paddle || !m_paddle->transform) {
        AC_ERROR("Breakout::Init() m_paddle or its transform is NULL!");
    }

    m_ball->transform->SetParent( m_paddle->transform );

    // once all the elements are created, now add them to the current active scene to be rendered
    GetCurrentLevel()->AddGameObject( m_background );
    GetCurrentLevel()->AddGameObject( m_ball );
    GetCurrentLevel()->AddGameObject( m_paddle );

    // move the bg to be the first thing to render, as it needs to be behind everything
    GetCurrentLevel()->MoveGameObjectToIndex( m_background, 0 );
}

// Clean up resources
void Breakout::Cleanup()
{
}

GameLevel *Breakout::GetCurrentLevel() const
{
    return m_levels[m_currentLevel];
}

void Breakout::SetCurrentLevel(int level)
{
    m_currentLevel = level - 1; 
    SceneManager::GetInstance()->SetActiveScene( GetCurrentLevel() );
}