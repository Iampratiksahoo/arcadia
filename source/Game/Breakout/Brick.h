#include "Engine/Core.h"

class Brick : public AbstractComponent
{
public:
    bool isSolid = false; 
    bool isDestroyed = false;

    void Reset() override; 
    void CollidedWithBall();
};