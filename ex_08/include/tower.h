#ifndef _TOWER_H_
#define _TOWER_H_

#include <cmath>
#include <tuple>
#include <iostream>

#include "transform.h"
#include "macros.h"
#include "cube.h"

#include <array>

class CubeTower
{
private:
    std::array<S_Cube, TOWER_MAX_SIZE> cubes;
    unsigned int nextBlockIndex = 0;
    unsigned int nbCubes = 0;
public:
    CubeTower()
    {
        reset();
    }

    ~CubeTower() {}

    bool addCubeOnTop(S_Cube& putCube);

    void draw();

    void reset();

    unsigned int getTowerSize()
    {
        return nbCubes;
    }
};




#endif 