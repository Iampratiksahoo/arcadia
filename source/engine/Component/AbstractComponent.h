#ifndef ABSTRACTCOMPONENT_H
#define ABSTRACTCOMPONENT_H


class GameObject;
class AbstractComponent
{
public:
    virtual void Reset() = 0; 

public:
    GameObject* gameObject; 
};

#endif