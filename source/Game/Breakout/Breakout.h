#pragma once

#include "Engine/Core.h" 
#include "GameLevel.h"

class Breakout : public AbstractGameBase
{
public:
    Breakout();
    ~Breakout();
    
    // Initialize the game
    void Init() override;

    const char* GetIniPath() override { return "source/Game/Breakout/Breakout.ini"; };

    // Clean up resources
    void Cleanup() override;

    GameLevel* GetCurrentLevel() const ;
    inline GameObject* GetPaddle() const { return m_paddle; }

    Vector2<float> GetWindowWidthAndHeight() { return Vector2<float>( getWindowWidth(), getWindowHeight() ); }

private:
    void SetCurrentLevel(int level);

private:
    std::vector<GameLevel*> m_levels; 
    uint m_currentLevel;

    GameObject* m_background;
    GameObject* m_paddle;
    GameObject* m_ball; 

    Vector2<float> m_paddleSize; 
    float m_paddleVelocity; 

    float m_ballRadius; 
    float m_ballVelocity; 
};