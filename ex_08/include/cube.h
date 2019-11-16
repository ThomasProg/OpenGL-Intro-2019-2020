#ifndef _CUBE_H_
#define _CUBE_H_

#include <cmath>
#include <tuple>
#include <iostream>

#include "transform.h"
#include "macros.h"

struct S_Cube
{
    vector3D minCoords;
    vector3D maxCoords;
    vector3D startCenter; //the movement won't change is the cube is cut

    S_Cube() {}

    S_Cube(const S_Cube& cube)
    {
        minCoords = cube.minCoords;
        maxCoords = cube.maxCoords;
    }

    S_Cube(vector3D minCoords, vector3D maxCoords) 
            : minCoords(minCoords), maxCoords(maxCoords), startCenter((maxCoords + minCoords) / 2.0) {}

    S_Cube cutBy(const S_Cube& edges);

    bool isInRange(const S_Cube& cube) const;

    
    //O(n^3) complexity
    //could be optimized : 
    // - to O(6 * n^2) complexity
    // - reduce glVertex3f call number
    void draw() const;

    static std::tuple<float, float, float> getColor(unsigned int id);

    static void moveAxis(float& center, float& min, float& max, float alpha);

    void movingCubeTick(bool axisIsX, float currentTime);
};

#endif