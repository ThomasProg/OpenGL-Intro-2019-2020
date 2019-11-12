#ifndef _MOVING_CUBE_H_
#define _MOVING_CUBE_H_

#include <cmath>
#include "mesh.h"

void moveCube(S_Cube& cube, float alpha)
{
    float sizeX = cube.maxCoords.x - cube.minCoords.x;
    cube.minCoords.x = std::sin(alpha)/10*3;
    cube.maxCoords.x = cube.minCoords.x + sizeX;
}

#endif