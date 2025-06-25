#include "Brick.h"

void Brick::Reset()
{
    isSolid = false;
    isDestroyed = false;
}

void Brick::CollidedWithBall()
{
    if ( !isSolid )
    {
        isDestroyed = true;
    }
}
