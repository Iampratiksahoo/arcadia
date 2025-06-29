#ifndef CIRCLECOLLIDER2D_H
#define CIRCLECOLLIDER2D_H

#include "AbstractCollider.h"
#include "BoxCollider2D.h"

class CircleCollider2D : public AbstractCollider 
{
public: 
    CircleCollider2D();
    float radius; 

protected:
    bool hasCollidedWith(AbstractCollider* otherCollider) const override;

private:
    bool hasCollidedWithBox(BoxCollider2D* boxCollider) const;
    bool hasCollidedWithCircle(CircleCollider2D* circleCollider) const;
}; 

#endif // CIRCLECOLLIDER2D_H