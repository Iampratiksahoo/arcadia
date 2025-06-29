#ifndef BOXCOLLIDER2D_H
#define BOXCOLLIDER2D_H

#include "Engine/Math/Core.h"
#include "AbstractCollider.h"

class BoxCollider2D : public AbstractCollider
{
public:
    BoxCollider2D();
    Vector2<float> size; 

protected:
    bool hasCollidedWith(AbstractCollider* otherCollider) const override;
};

#endif // BOXCOLLIDER2D_H