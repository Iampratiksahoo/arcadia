#ifndef ABSTRACTCOMPONENT_H
#define ABSTRACTCOMPONENT_H


class GameObject;
class Transform; 
class AbstractComponent
{
public:
    virtual void Reset() = 0; 

public:
    GameObject* gameObject; 
    Transform* transform; 
};

#endif