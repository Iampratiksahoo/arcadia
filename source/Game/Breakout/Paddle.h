#include "Engine/Core.h"

class Paddle : public AbstractComponent
{
public:
    Paddle();
    void Update(float deltaTime) override; 

    inline void SetGameInstance( class Breakout* instance) { m_gameInstance = instance; }

public:
    Vector2<float> size; 

private:
    class Breakout* m_gameInstance;
    float m_velocity; 
};