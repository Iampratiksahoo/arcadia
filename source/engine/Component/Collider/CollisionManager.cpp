#include "CollisionManager.h"

#include "AbstractCollider.h"
#include "Engine/Core/GameObject.h"

void CollisionManager::fixedUpdate(float fixedDeltaTime)
{
    // outer loop, to loop through each collider
    for(AbstractCollider* collider1 : m_colliders)
    {
        // check if the collider1 is not destroyed
        // and is active in the scene 
        if(collider1 != nullptr
            && collider1->gameObject->IsActive())
        {
            // inner loop, to loop through each collider again
            for(AbstractCollider* collider2 : m_colliders)
            {
                // also check if the collider2 is not destroyed
                // and is active in the scene 
                if(collider2 != nullptr
                    && collider2->gameObject->IsActive())
                {
                    // we don't check with oneself 
                    if(collider1->GetUuid() != collider2->GetUuid()
                        && collider1->hasCollidedWith( collider2 ))
                    {
                        collider1->gameObject->onCollisionEnter(collider2);
                        collider2->gameObject->onCollisionEnter(collider1);
                    }
                }
            }   
        }
    }
}

void CollisionManager::addCollider(AbstractCollider *collider)
{
    if(collider != nullptr)
    {
        const std::string& uuid = collider->GetUuid();

        if (m_colliderUUIDs.find(uuid) == m_colliderUUIDs.end()) 
        {
            m_colliders.push_back(collider);
            m_colliderUUIDs.insert(uuid);
        }
    }
}

void CollisionManager::removeCollider(AbstractCollider *collider)
{
    if(collider != nullptr)
    {
        const std::string& uuid = collider->GetUuid();
        auto it = std::find(m_colliders.begin(), m_colliders.end(), collider);
        if (it != m_colliders.end()) 
        {
            m_colliders.erase(it);
            m_colliderUUIDs.erase(uuid);
        }
    }
}
