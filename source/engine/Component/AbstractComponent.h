#ifndef ABSTRACTCOMPONENT_H
#define ABSTRACTCOMPONENT_H


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

    /// @brief Never called, explicitly need to call this 
    virtual void Reset() { }

protected:
    friend GameObject;
    ~AbstractComponent() = default; 

public:
    GameObject* gameObject; 
    Transform* transform; 
};

#endif