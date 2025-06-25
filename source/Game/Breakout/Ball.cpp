#include "Ball.h"
#include "Breakout.h"
#include "Brick.h"

Ball::Ball()
{
    m_moveDirection = Vector3<float>(1.f, 1.f, 0.f);
}

void Ball::Reset()
{

}

bool Ball::checkCollision(GameObject *other) const
{
    Transform* ballT = gameObject->transform;
    SpriteRenderer* ballSR = gameObject->GetComponent<SpriteRenderer>();

    Transform* otherT = other->transform;
    SpriteRenderer* otherSR = other->GetComponent<SpriteRenderer>();

    // Ball center position
    Vector2<float> ballCenter(
        ballT->GetPosition().x + m_radius,
        ballT->GetPosition().y + m_radius
    );

    // AABB center position and half extents
    Vector2<float> aabbHalfExtents = otherSR->GetSize() / 2.0f;
    Vector2<float> aabbCenter(
        otherT->GetPosition().x + aabbHalfExtents.x,
        otherT->GetPosition().y + aabbHalfExtents.y
    );

    // Calculate difference vector between both centers
    Vector2<float> difference = ballCenter - aabbCenter;

    // Clamp to AABB extents
    Vector2<float> clamped = Vector2<float>::Clamp(difference, -aabbHalfExtents, aabbHalfExtents);

    // Closest point on AABB to the ball
    Vector2<float> closest = aabbCenter + clamped;

    // Vector between circle center and closest point
    Vector2<float> distanceVec = closest - ballCenter;

    // Check if within m_radius (circle vs AABB)
    return distanceVec.SquareMagnitude() < m_radius * m_radius;
}

Vector3<float> Ball::reflect(Vector3<float> direction, Vector3<float> normal)
{
    Vector3<float> reflection = direction - (normal * 2.0f * direction.Dot(normal)); 
    reflection.z = 0;
    return reflection;
}

void Ball::Move(float deltaTIme, float velocity, int windowWidth, int windowHeight)
{
    if( !isStuck )
    {
        Transform* objTransform = gameObject->transform;
        float errorMargin = 20.f; 
    
        if( objTransform->GetPosition().x <= 0 )
        {
            m_moveDirection.x = -1.f;
        }
        if( objTransform->GetPosition().x >= windowWidth - errorMargin )
        {
            m_moveDirection.x = 1.f;
        }
        if( objTransform->GetPosition().y <= 0 )
        {
            m_moveDirection.y = -1.f;
        }

        // now check for collision with bricks 
        for(GameObject* brickObj : m_gameInstance->GetCurrentLevel()->GetBricks() )
        {
            Brick* brick = brickObj->GetComponent<Brick>();

            // change the direction, only if the object is not destroyed this frame
            if(!brick->isDestroyed)
            {
                if( checkCollision( brickObj ) )
                {
                    // now change the direction of the
                    m_moveDirection = reflect(m_moveDirection, getCollisionNormal( brickObj ));

                    // handle the collision with ball for the brick 
                    brick->CollidedWithBall();
                }
            }
        }

        // now check the collision with paddle 
        if( checkCollision( m_gameInstance->GetPaddle() ))
        {
            // now change the direction of the
            m_moveDirection = reflect(m_moveDirection, getCollisionNormal( m_gameInstance->GetPaddle() )); 
        }   

        // move the ball
        objTransform->Translate( m_moveDirection * -velocity * deltaTIme );
    }
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