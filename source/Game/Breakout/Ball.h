#include "Engine/Core.h"

class Ball : public AbstractComponent 
{
public:
    Ball();
    void Reset() override; 

    void Move(float deltaTIme, float velocity, int windowWidth, int windowHeight);
    void SetRadius(float radius);
    inline float GetRadius() const { return m_radius; }
    
    bool isStuck = true; 
    
    inline void SetGameInstance( class Breakout* instance) { m_gameInstance = instance; }
    
private:
    bool checkCollision(GameObject* other) const;
    Vector3<float> reflect (Vector3<float> direction, Vector3<float> normal);
    Vector3<float> getCollisionNormal( GameObject* other) const;

private:
    float m_radius; 
    class Breakout* m_gameInstance;
    Vector3<float> m_moveDirection; 
};