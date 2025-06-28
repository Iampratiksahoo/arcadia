#include "Paddle.h"
#include "Breakout.h"

Paddle::Paddle()
{
    m_velocity = 500.f;
}

void Paddle::Update(float deltaTime)
{
    int windowWidth = m_gameInstance->GetWindowWidthAndHeight().x;
    Vector3<float> translation;
    
    if(Input::GetKey(KeyCode::A)
        && transform->GetPosition().x > 0 )
    {
        translation = Vector3<float>::Left;
    }
    if(Input::GetKey(KeyCode::D)
        && transform->GetPosition().x < windowWidth - size.x)
    {
        translation = Vector3<float>::Right;
    }

    transform->Translate( translation * m_velocity * deltaTime );
}