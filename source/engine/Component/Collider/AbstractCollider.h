#ifndef ABSTRACTCOLLIDER_H
#define ABSTRACTCOLLIDER_H

#include "Engine/Component/AbstractComponent.h"

class AbstractCollider : public AbstractComponent
{
protected:
    friend class CollisionManager;

    virtual bool hasCollidedWith(AbstractCollider* otherCollider) const = 0;
};

#endif // ABSTRACTCOLLIDER_H