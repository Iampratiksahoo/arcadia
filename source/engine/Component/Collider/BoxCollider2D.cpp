#include "BoxCollider2D.h"

#include "Engine/Core/GameObject.h"

BoxCollider2D::BoxCollider2D()
{
    size = Vector2<float>::One * 10.f;
}

bool BoxCollider2D::hasCollidedWith(AbstractCollider *otherCollider) const
{
    bool hasCollided = false;

    // we only check against the box collider for now 
    // because the circle collider will already check againt a boxCollider
    if( BoxCollider2D* boxCollider = dynamic_cast<BoxCollider2D*>( otherCollider ) )
    {
        Vector3<float> thisPos = transform->GetPosition();
        Vector3<float> otherPos = otherCollider->transform->GetPosition();
        
        // collision x-axis?
        bool collisionX = thisPos.x + size.x >= otherPos.x &&
            otherPos.x + boxCollider->size.x >= thisPos.x;

        // collision y-axis?
        bool collisionY = thisPos.y + size.y >= otherPos.y &&
            otherPos.y + boxCollider->size.y >= thisPos.y;

        // collision only if on both axes
        hasCollided = collisionX && collisionY;
    }

    return hasCollided;
}