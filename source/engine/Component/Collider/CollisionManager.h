#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "Engine/Util/DesignPatterns/SingletonBase.h"
#include "Engine/AbstractSystemManager.h"
#include "AbstractCollider.h"

#include <vector>
#include <unordered_set>

class CollisionManager : public AbstractSystemManager, public SingletonBase<CollisionManager> 
{
private: 
    friend class AbstractCollider; 
    friend class GameObject;

    void fixedUpdate(float fixedDeltaTime) override;
    
    void addCollider(AbstractCollider* collider); 
    void removeCollider(AbstractCollider* collider);

private:    
    std::unordered_set<std::string> m_colliderUUIDs;
    std::vector<AbstractCollider*> m_colliders; 
}; 

#endif // COLLISIONMANAGER_H