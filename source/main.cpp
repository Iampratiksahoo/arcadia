#include "core/Engine.h"
#include "game/Breakout.h"

int main ( void ) 
{
    IGame *game = new Breakout();
    Engine engine { *game };
    return 0;
}
