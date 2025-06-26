#include "Brick.h"

void Brick::Reset()
{
    isSolid = false;
}

void Brick::CollidedWithBall()
{
    if ( !isSolid )
    {
        gameObject->SetActive( false );
    }
}
