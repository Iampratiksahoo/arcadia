#ifndef ABSTRACTCOMPONENT_H
#define ABSTRACTCOMPONENT_H

#include <string>
#include "Engine/Util/UUID.h"

class GameObject;
class Transform; 
class AbstractComponent
{
public:
    /// @brief Called when the game actually starts
    virtual void OnGameStart() { }

    /// @brief Called when the active state of the component is changed
    virtual void OnActiveStateChange(bool active) { }

    /// @brief Called every frame
    virtual void Update(float deltaTime) { }

    /// @brief Called once per fixed frame time, best for collision and physics calculation
    virtual void FixedUpdate(float fixedDeltaTime) { }

    /// @brief Called when the GameObject is collided with another collider
    virtual void OnCollisionEnter( class AbstractCollider* other ) { }

    /// @brief Never called, explicitly need to call this 
    virtual void Reset() { }

    /// @brief Get UUID unique to this component  
    inline const std::string& GetUuid() const { return m_uuid; };

protected:
    friend GameObject;
    AbstractComponent() : m_uuid( UUID::GenerateUUID() ) {  }
    ~AbstractComponent() = default; 

public:
    GameObject* gameObject; 
    Transform* transform; 

private:
    std::string m_uuid; 
};

#endif