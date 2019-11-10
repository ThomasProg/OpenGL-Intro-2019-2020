#ifndef _MESH_H_
#define _MESH_H_

constexpr float CUBE_SIZE = 10.f;
constexpr float CUBE_HALF_SIZE = CUBE_SIZE / 2.f;

struct vector3D
{
    float x, y, z;
    vector3D() : x(0), y(0), z(0) {}
    vector3D(float x, float y, float z) : x(x), y(x), z(z) {}
    vector3D(const vector3D& v) : x(v.x), y(v.x), z(v.z) {}
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

    S_Cube(vector3D minCoords, vector3D maxCoords) 
            : minCoords(minCoords), maxCoords(maxCoords) {}

    S_Cube cutBy(const S_Cube& edges) const
    {
        S_Cube cutCube;
        cutCube.minCoords.x = std::max(minCoords.x, edges.minCoords.x); 
        cutCube.minCoords.y = std::max(minCoords.y, edges.minCoords.y); 
        cutCube.maxCoords.x = std::min(maxCoords.x, edges.maxCoords.x); 
        cutCube.maxCoords.y = std::min(maxCoords.y, edges.maxCoords.y); 
        return cutCube;
    }

    void draw() const
    {
        
    }
};

#include <array>
#define TOWER_MAX_SIZE 10

class CubeTower
{
private:
    std::array<S_Cube, TOWER_MAX_SIZE> cubes;
    unsigned int nextBlockIndex = 0;
public:
    CubeTower()
    {
        cubes[0] = S_Cube(vector3D(-CUBE_HALF_SIZE, -CUBE_HALF_SIZE, -CUBE_HALF_SIZE), 
                          vector3D(CUBE_SIZE, CUBE_SIZE, CUBE_SIZE));
    }

    ~CubeTower() {}

    // void addCube(const S_Cube& cube)
    // {
    //     cubes[nextBlockIndex] = cube;

    //     nextBlockIndex++;
    //     nextBlockIndex %= TOWER_MAX_SIZE;
    // }

    void addCubeOnTop(const S_Cube& putCube)
    {
        unsigned int prevIndex = nextBlockIndex < 1 ? TOWER_MAX_SIZE - 1 : nextBlockIndex - 1;
        
        cubes[nextBlockIndex] = putCube.cutBy(cubes[prevIndex]);

        nextBlockIndex++;
        nextBlockIndex %= TOWER_MAX_SIZE;
    }

    void draw()
    {
        for (const S_Cube& cube : cubes)
        {
            cube.draw();
        }
    }
};

class Mesh
{

};

// vector2D cutRange(vector2D toCut, vector2D r)
// {
//     return vector2D(toCut.x)

// }

void cutSquare()
{
    float x, y;
}



#endif 