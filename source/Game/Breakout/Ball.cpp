#include "Ball.h"
#include "Breakout.h"
#include "Brick.h"

Ball::Ball()
{
    m_moveDirection = Vector3<float>(1.f, 1.f, 0.f);
    m_velocity = 350.f; 
}

void Ball::Update(float deltaTime)
{
    if(Input::GetKeyDown(KeyCode::SPACE))
    {
        if(transform->GetParent() != nullptr)
        {
            AC_NOTICE("Current Parent: %s", transform->GetParent()->gameObject->name.c_str());
            transform->SetParent(nullptr);
            isStuck = false;
        }
    }
}

void Ball::FixedUpdate(float fixedDeltaTime)
{
    if( !isStuck )
    {
        Transform* objTransform = gameObject->transform;
        float errorMargin = 20.f; 
    
        if( objTransform->GetPosition().x <= 0 )
        {
            m_moveDirection.x = -1.f;
        }
        if( objTransform->GetPosition().x >= m_gameInstance->GetWindowWidthAndHeight().x - errorMargin )
        {
            m_moveDirection.x = 1.f;
        }
        if( objTransform->GetPosition().y <= 0 )
        {
            m_moveDirection.y = -1.f;
        }

        Vector3<float> translation = m_moveDirection * -m_velocity * fixedDeltaTime;

        // move the ball
        objTransform->Translate( translation );
    }
}

void Ball::OnCollisionEnter(AbstractCollider *other)
{
    if(!isStuck)
    {
        if(Brick* brick = other->gameObject->GetComponent<Brick>())
        {
            // now change the direction of the ball
            m_moveDirection = reflect(m_moveDirection, getCollisionNormal( other->gameObject ));
    
            // handle collision for the ball
            brick->CollidedWithBall();
        }
    
        // now check the collision with paddle 
        if( other->gameObject ==  m_gameInstance->GetPaddle() )
        {
            // now change the direction of the
            m_moveDirection = reflect(m_moveDirection, getCollisionNormal( m_gameInstance->GetPaddle() )); 
        }   
    }
}

Vector3<float> Ball::reflect(Vector3<float> direction, Vector3<float> normal)
{
    Vector3<float> reflection = direction - (normal * 2.0f * direction.Dot(normal)); 
    reflection.z = 0;
    return reflection;
}

void Ball::SetRadius(float radius)
{
    if( SpriteRenderer* renderer = gameObject->GetComponent<SpriteRenderer>() )
    {
        m_radius = radius; 

        renderer->SetSize(
            Vector2<float>(radius) * 2.f
        );
    }
}

Vector3<float> Ball::getCollisionNormal(GameObject* other) const
{
    Transform* ballT = gameObject->transform;
    SpriteRenderer* ballSR = gameObject->GetComponent<SpriteRenderer>();

    Transform* otherT = other->transform;
    SpriteRenderer* otherSR = other->GetComponent<SpriteRenderer>();

    Vector2<float> ballCenter(
        ballT->GetPosition().x + m_radius,
        ballT->GetPosition().y + m_radius
    );

    Vector2<float> aabbHalfExtents = otherSR->GetSize() / 2.0f;
    Vector2<float> aabbCenter(
        otherT->GetPosition().x + aabbHalfExtents.x,
        otherT->GetPosition().y + aabbHalfExtents.y
    );

    Vector2<float> difference = ballCenter - aabbCenter;
    Vector2<float> clamped = Vector2<float>::Clamp(difference, -aabbHalfExtents, aabbHalfExtents);
    Vector2<float> closest = aabbCenter + clamped;

    Vector2<float> normal = (ballCenter - closest).GetNormalized();

    return Vector3<float>(normal.x, normal.y, 0);
}