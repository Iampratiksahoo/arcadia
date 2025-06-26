#include "Engine/Core.h"

class Brick : public AbstractComponent
{
public:
    bool isSolid = false; 

    void Reset() override; 
    void CollidedWithBall();
};