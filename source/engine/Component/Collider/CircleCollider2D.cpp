#include "CircleCollider2D.h"

#include "Engine/Component/Transform.h"

CircleCollider2D::CircleCollider2D()
{
    radius = 10.f;
}

bool CircleCollider2D::hasCollidedWith(AbstractCollider *otherCollider) const
{
    bool hasCollided = false;

    if(BoxCollider2D* boxCollider = dynamic_cast<BoxCollider2D*>(otherCollider))
    {
        hasCollided = hasCollidedWithBox( boxCollider );
    }
    else if(CircleCollider2D* circleCollider = dynamic_cast<CircleCollider2D*>(otherCollider))
    {
        hasCollided = hasCollidedWithCircle(circleCollider);
    }

    return hasCollided; 
}

bool CircleCollider2D::hasCollidedWithBox(BoxCollider2D *boxCollider) const
{
    // Ball center position
    Vector2<float> ballCenter(
        transform->GetPosition().x + radius,
        transform->GetPosition().y + radius
    );

    // AABB center position and half extents
    Vector2<float> aabbHalfExtents = boxCollider->size / 2.0f;
    Vector2<float> aabbCenter(
        boxCollider->transform->GetPosition().x + aabbHalfExtents.x,
        boxCollider->transform->GetPosition().y + aabbHalfExtents.y
    );

    // Calculate difference vector between both centers
    Vector2<float> difference = ballCenter - aabbCenter;

    // Clamp to AABB extents
    Vector2<float> clamped = Vector2<float>::Clamp(difference, -aabbHalfExtents, aabbHalfExtents);

    // Closest point on AABB to the ball
    Vector2<float> closest = aabbCenter + clamped;

    // Vector between circle center and closest point
    Vector2<float> distanceVec = closest - ballCenter;

    // Check if within radius (circle vs AABB)
    return distanceVec.SquareMagnitude() < radius * radius;
}

bool CircleCollider2D::hasCollidedWithCircle(CircleCollider2D *circleCollider) const
{
    // Calculate the centers of both circles
    Vector2<float> centerThis(
        transform->GetPosition().x + radius,
        transform->GetPosition().y + radius
    );

    Vector2<float> centerOther(
        circleCollider->transform->GetPosition().x + circleCollider->radius,
        circleCollider->transform->GetPosition().y + circleCollider->radius
    );

    // Vector between centers
    Vector2<float> difference = centerThis - centerOther;

    // Compute squared distance
    float distanceSquared = difference.SquareMagnitude();

    // Compute squared sum of radii
    float combinedRadius = radius + circleCollider->radius;
    float combinedRadiusSquared = combinedRadius * combinedRadius;

    // Collision occurs if distance squared < combined radii squared
    return distanceSquared < combinedRadiusSquared;
}
