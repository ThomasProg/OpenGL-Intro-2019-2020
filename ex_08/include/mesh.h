#ifndef _MESH_H_
#define _MESH_H_

#include <iostream>

constexpr float CUBE_SIZE = 0.1f;
constexpr float CUBE_HALF_SIZE = CUBE_SIZE / 2.f;

struct vector3D
{
    float x, y, z;
    vector3D() : x(0), y(0), z(0) {}
    vector3D(float x, float y, float z) : x(x), y(y), z(z) {}
    vector3D(const vector3D& v) : x(v.x), y(v.y), z(v.z) {}
};

struct vector2D
{
    float x, y;
};

struct S_Cube
{
    vector3D minCoords;
    vector3D maxCoords;

    S_Cube() {}

    S_Cube(const S_Cube& cube)
    {
        minCoords = cube.minCoords;
        maxCoords = cube.maxCoords;
    }

    S_Cube(vector3D minCoords, vector3D maxCoords) 
            : minCoords(minCoords), maxCoords(maxCoords) {}

    S_Cube cutBy(const S_Cube& edges)
    {
        //S_Cube cutCube = *this;
        // cutCube.minCoords.x = edges.minCoords.x - 10;
        // cutCube.minCoords.y = edges.minCoords.y+1;
        // cutCube.minCoords.z = edges.minCoords.z; 
        // cutCube.maxCoords.x = edges.maxCoords.x + 10;
        // cutCube.maxCoords.y = edges.maxCoords.y+1; 
        // cutCube.maxCoords.z = edges.maxCoords.z; 
        
        minCoords.x = std::max(minCoords.x, edges.minCoords.x); 
        minCoords.z = std::max(minCoords.z, edges.minCoords.z); 
        maxCoords.x = std::min(maxCoords.x, edges.maxCoords.x); 
        maxCoords.z = std::min(maxCoords.z, edges.maxCoords.z); 


        // cutCube.minCoords.x = std::max(minCoords.x, edges.minCoords.x); 
        // cutCube.minCoords.y = 1.f;
        // cutCube.minCoords.z = std::max(minCoords.z, edges.minCoords.z); 
        // cutCube.maxCoords.x = std::min(maxCoords.x, edges.maxCoords.x); 
        // cutCube.maxCoords.y = 1.f;
        // cutCube.maxCoords.z = std::min(maxCoords.z, edges.maxCoords.z); 
        return *this;
    }

    void drawFace(vector3D p1, vector3D p2) const
    {
        glVertex3f(p1.x, p1.y, p1.z);
        glVertex3f(p2.x, p1.y, p1.z);
        glVertex3f(p2.x, p2.y, p1.z);
        glVertex3f(p1.x, p2.y, p1.z);

        glVertex3f(p1.x, p1.y, p2.z);
        glVertex3f(p2.x, p1.y, p2.z);
        glVertex3f(p2.x, p2.y, p2.z);
        glVertex3f(p1.x, p2.y, p2.z);

        glVertex3f(p1.x, p1.y, p1.z);
        glVertex3f(p1.x, p1.y, p2.z);
        glVertex3f(p1.x, p2.y, p2.z);
        glVertex3f(p1.x, p2.y, p1.z);

        glVertex3f(p2.x, p1.y, p1.z);
        glVertex3f(p2.x, p1.y, p2.z);
        glVertex3f(p2.x, p2.y, p2.z);
        glVertex3f(p2.x, p2.y, p1.z);

        glVertex3f(p1.x, p1.y, p1.z);
        glVertex3f(p1.x, p1.y, p2.z);
        glVertex3f(p2.x, p1.y, p2.z);
        glVertex3f(p2.x, p1.y, p1.z);

        glVertex3f(p1.x, p2.y, p1.z);
        glVertex3f(p1.x, p2.y, p2.z);
        glVertex3f(p2.x, p2.y, p2.z);
        glVertex3f(p2.x, p2.y, p1.z);
    }

    bool isInRange(const S_Cube& cube) const
    {
        std::cout << "x1 : " << minCoords.x << " / xmax : " << maxCoords.x << std::endl;
        std::cout << "x2 : " << cube.minCoords.x << " / xmax2 : " << cube.maxCoords.x << std::endl;

        return minCoords.x <= cube.maxCoords.x && maxCoords.x >= cube.minCoords.x;
    }

    void draw() const
    {
        drawFace(minCoords, maxCoords);
    }
};

#include <array>
#define TOWER_MAX_SIZE 50

class CubeTower
{
private:
    std::array<S_Cube, TOWER_MAX_SIZE> cubes;
    unsigned int nextBlockIndex = 0;
    unsigned int nbCubes = 0;
public:
    CubeTower()
    {
        cubes[0] = S_Cube(vector3D(0, 0, 0), 
                          vector3D(CUBE_SIZE, CUBE_SIZE, CUBE_SIZE));

        nbCubes++;
        nextBlockIndex++;

        // S_Cube cube = cubes[0];
        // cube.maxCoords.y += 1;
        // cube.minCoords.y += 1;
        // cube.minCoords.x = -5;
        // addCubeOnTop(cube);
    }

    ~CubeTower() {}

    // void addCube(const S_Cube& cube)
    // {
    //     cubes[nextBlockIndex] = cube;

    //     nextBlockIndex++;
    //     nextBlockIndex %= TOWER_MAX_SIZE;
    // }

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
};

// class Mesh
// {

// };

// vector2D cutRange(vector2D toCut, vector2D r)
// {
//     return vector2D(toCut.x)

// }

void cutSquare()
{
    float x, y;
}



#endif 