#include "game/Breakout.h"

int main ( void ) 
{
    AbstractGameBase *game = new Breakout();
    Engine engine { *game };
    return 0;
}
