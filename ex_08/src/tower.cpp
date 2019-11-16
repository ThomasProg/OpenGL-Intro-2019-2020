#include "tower.h"

bool CubeTower::addCubeOnTop(S_Cube& putCube)
{
    unsigned int prevIndex = nextBlockIndex < 1 ? TOWER_MAX_SIZE - 1 : nextBlockIndex - 1;
    
    if (!putCube.isInRange(cubes[prevIndex]))
        return false;

    cubes[nextBlockIndex] = putCube.cutBy(cubes[prevIndex]);

    nextBlockIndex++;
    nbCubes++;
    nextBlockIndex %= TOWER_MAX_SIZE;
    return true;
}

void CubeTower::draw()
{
    glBegin(GL_QUADS);
    unsigned int n = (nbCubes < TOWER_MAX_SIZE ? nbCubes : TOWER_MAX_SIZE);
    for (unsigned int i = 0; i < n; i++)
    {
        float rgb[3];
        std::tie(rgb[0], rgb[1], rgb[2]) = S_Cube::getColor(i);
        glColor3f(rgb[0], rgb[1], rgb[2]);
        cubes[i].draw();
    }
    glEnd();
}

void CubeTower::reset()
{
    cubes[0] = S_Cube(vector3D(-CUBE_HALF_SIZE, -CUBE_HALF_HEIGHT, -CUBE_HALF_SIZE), 
                        vector3D(CUBE_HALF_SIZE, CUBE_HALF_HEIGHT, CUBE_HALF_SIZE));

    nbCubes = 1;
    nextBlockIndex = 1;
}