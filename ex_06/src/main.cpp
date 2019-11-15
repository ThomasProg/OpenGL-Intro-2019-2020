#include <cstdio>

// #include "macros.h"
// #include "mesh.h"
// #include "sphere.h"
// #include "cube.h"
// #include "utilities.h"
// #include "camera.h"
// #include "maze.h"

#include "game.h"

int main()
{
    bool isValid = true;
    Game game(isValid);
    if (isValid)
        game.loop();
}
