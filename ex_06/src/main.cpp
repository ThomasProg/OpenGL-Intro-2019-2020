#include <cstdio>

#include "game.h"

int main()
{
    bool isValid = true;
    Game game(isValid);
    if (isValid)
        game.loop();
}
