#ifndef _MESH_H_
#define _MESH_H_

#include <iostream>
#include "transform.h"

constexpr float CUBE_SIZE   = 0.5f;
constexpr float CUBE_HEIGHT = 0.1f;

constexpr float CUBE_HALF_SIZE = CUBE_SIZE / 2;
constexpr float CUBE_HALF_HEIGHT    = CUBE_HEIGHT / 2;

constexpr float moveDistance = 1; 
constexpr float moveSpeed    = 1;

// struct vector3D
// {
//     float x, y, z;
//     vector3D() : x(0), y(0), z(0) {}
//     vector3D(float x, float y, float z) : x(x), y(y), z(z) {}
//     vector3D(const vector3D& v) : x(v.x), y(v.y), z(v.z) {}
// };

struct vector2D
{
    float x, y;
};

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

    S_Cube cutBy(const S_Cube& edges)
    {
        minCoords.x = std::max(minCoords.x, edges.minCoords.x); 
        minCoords.z = std::max(minCoords.z, edges.minCoords.z); 
        maxCoords.x = std::min(maxCoords.x, edges.maxCoords.x); 
        maxCoords.z = std::min(maxCoords.z, edges.maxCoords.z); 

        return *this;
    }

    bool isInRange(const S_Cube& cube) const
    {
        return minCoords.x <= cube.maxCoords.x && maxCoords.x >= cube.minCoords.x
            && minCoords.z <= cube.maxCoords.z && maxCoords.z >= cube.minCoords.z;
    }

    void draw() const
    {
        glVertex3f(minCoords.x, minCoords.y, minCoords.z);
        glVertex3f(maxCoords.x, minCoords.y, minCoords.z);
        glVertex3f(maxCoords.x, maxCoords.y, minCoords.z);
        glVertex3f(minCoords.x, maxCoords.y, minCoords.z);

        glVertex3f(minCoords.x, minCoords.y, maxCoords.z);
        glVertex3f(maxCoords.x, minCoords.y, maxCoords.z);
        glVertex3f(maxCoords.x, maxCoords.y, maxCoords.z);
        glVertex3f(minCoords.x, maxCoords.y, maxCoords.z);

        glVertex3f(minCoords.x, minCoords.y, minCoords.z);
        glVertex3f(minCoords.x, minCoords.y, maxCoords.z);
        glVertex3f(minCoords.x, maxCoords.y, maxCoords.z);
        glVertex3f(minCoords.x, maxCoords.y, minCoords.z);

        glVertex3f(maxCoords.x, minCoords.y, minCoords.z);
        glVertex3f(maxCoords.x, minCoords.y, maxCoords.z);
        glVertex3f(maxCoords.x, maxCoords.y, maxCoords.z);
        glVertex3f(maxCoords.x, maxCoords.y, minCoords.z);

        glVertex3f(minCoords.x, minCoords.y, minCoords.z);
        glVertex3f(minCoords.x, minCoords.y, maxCoords.z);
        glVertex3f(maxCoords.x, minCoords.y, maxCoords.z);
        glVertex3f(maxCoords.x, minCoords.y, minCoords.z);

        glVertex3f(minCoords.x, maxCoords.y, minCoords.z);
        glVertex3f(minCoords.x, maxCoords.y, maxCoords.z);
        glVertex3f(maxCoords.x, maxCoords.y, maxCoords.z);
        glVertex3f(maxCoords.x, maxCoords.y, minCoords.z);
    }

    static void moveAxis(float& center, float& min, float& max, float alpha)
    {
        float delta = center;
        center      = std::sin(alpha * moveSpeed) * moveDistance;
        delta       -= center;

        max -= delta;
        min -= delta;
    }

    void movingCubeTick(bool axisIsX, float currentTime)
    {
        glColor3f(0,0,1);
        //move cube
        if (axisIsX)
            moveAxis(startCenter.x, minCoords.x, maxCoords.x, currentTime);
        else 
            moveAxis(startCenter.z, minCoords.z, maxCoords.z, currentTime);

        glBegin(GL_QUADS);
        draw();
        glEnd();
    }
};

#include <array>
#define TOWER_MAX_SIZE 10000

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

    bool addCubeOnTop(S_Cube& putCube)
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

    void draw()
    {
        glBegin(GL_QUADS);
        unsigned int n = (nbCubes < TOWER_MAX_SIZE ? nbCubes : TOWER_MAX_SIZE);
        for (unsigned int i = 0; i < n; i++)
        {
            float f = float(i) / float(n);
            glColor3f(0, f, 0);
            cubes[i].draw();
        }
        glEnd();
    }

    void reset()
    {
        cubes[0] = S_Cube(vector3D(-CUBE_HALF_SIZE, -CUBE_HALF_HEIGHT, -CUBE_HALF_SIZE), 
                          vector3D(CUBE_HALF_SIZE, CUBE_HALF_HEIGHT, CUBE_HALF_SIZE));

        nbCubes = 1;
        nextBlockIndex = 1;
    }

    unsigned int getTowerSize()
    {
        return nbCubes;
    }
};




#endif 