#ifndef ABSTRACTSYSTEMMANAGER_H
#define ABSTRACTSYSTEMMANAGER_H

#include "Engine/Util/DesignPatterns/SingletonBase.h"

class AbstractSystemManager
{
private:
    friend class Engine; 

    virtual void gameStart() { }
    virtual void update(float deltaTime) { }
    virtual void fixedUpdate(float fixedDeltaTime) { }
    virtual void render() { }
    virtual void cleanup() { }
}; 

#endif // ABSTRACTSYSTEMMANAGER_H