#ifndef _MESH_H_
#define _MESH_H_

#include <tuple>
#include <iostream>
#include "transform.h"

#include "mesh2.h"
#include "sphere.h"

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

    // static void splitFace(vector3D min, vector3D max, const vector3D& normal)
    // {
    //     glVertex3f(min.x, min.y, min.z);
    //     glVertex3f(max.x, min.y, min.z);
    //     glVertex3f(max.x, maxCoords.y, min.z);
    //     glVertex3f(min.x, maxCoords.y, minCoords.z);
    // }

    void draw() const
    {
        constexpr unsigned int nbDivisions = 10;
        float deltaX = maxCoords.x - minCoords.x;
        float deltaY = maxCoords.y - minCoords.y;
        float deltaZ = maxCoords.z - minCoords.z;
        for (unsigned int i = 0; i < nbDivisions; i++)
        {
            for (unsigned int j = 0; j < nbDivisions; j++)
            {
                for (unsigned int k = 0; k < nbDivisions; k++)
                {
                    if (i == 0 || i == nbDivisions - 1 || 
                        j == 0 || j == nbDivisions - 1 ||
                        k == 0 || k == nbDivisions - 1)
                    {
                    const float minX = minCoords.x + deltaX * i / float(nbDivisions);
                    const float minY = minCoords.y + deltaY * j / float(nbDivisions);
                    const float minZ = minCoords.z + deltaZ * k / float(nbDivisions);

                    const float maxX = minCoords.x + deltaX * (i+1) / float(nbDivisions);
                    const float maxY = minCoords.y + deltaY * (j+1) / float(nbDivisions);
                    const float maxZ = minCoords.z + deltaZ * (k+1) / float(nbDivisions);

                    glNormal3f(0, 0, -1);
                    glVertex3f(minX, minY, minZ);
                    glVertex3f(maxX, minY, minZ);
                    glVertex3f(maxX, maxY, minZ);
                    glVertex3f(minX, maxY, minZ);

                    glNormal3f(0, 0, 1);
                    glVertex3f(minX, minY, maxZ);
                    glVertex3f(maxX, minY, maxZ);
                    glVertex3f(maxX, maxY, maxZ);
                    glVertex3f(minX, maxY, maxZ);

                    glNormal3f(-1, 0, 0);
                    glVertex3f(minX, minY, minZ);
                    glVertex3f(minX, minY, maxZ);
                    glVertex3f(minX, maxY, maxZ);
                    glVertex3f(minX, maxY, minZ);

                    glNormal3f(1, 0, 0);
                    glVertex3f(maxX, minY, minZ);
                    glVertex3f(maxX, minY, maxZ);
                    glVertex3f(maxX, maxY, maxZ);
                    glVertex3f(maxX, maxY, minZ);

                    glNormal3f(0, -1, 0);
                    glVertex3f(minX, minY, minZ);
                    glVertex3f(minX, minY, maxZ);
                    glVertex3f(maxX, minY, maxZ);
                    glVertex3f(maxX, minY, minZ);

                    glNormal3f(0, 1, 0);
                    glVertex3f(minX, maxY, minZ);
                    glVertex3f(minX, maxY, maxZ);
                    glVertex3f(maxX, maxY, maxZ);
                    glVertex3f(maxX, maxY, minZ);
                    }
                } 
            }
        }

            // glNormal3f(0, 0, -1);
            // glVertex3f(minCoords.x, minCoords.y, minCoords.z);
            // glVertex3f(maxCoords.x, minCoords.y, minCoords.z);
            // glVertex3f(maxCoords.x, maxCoords.y, minCoords.z);
            // glVertex3f(minCoords.x, maxCoords.y, minCoords.z);

            // glNormal3f(0, 0, 1);
            // glVertex3f(minCoords.x, minCoords.y, maxCoords.z);
            // glVertex3f(maxCoords.x, minCoords.y, maxCoords.z);
            // glVertex3f(maxCoords.x, maxCoords.y, maxCoords.z);
            // glVertex3f(minCoords.x, maxCoords.y, maxCoords.z);

            // glNormal3f(-1, 0, 0);
            // glVertex3f(minCoords.x, minCoords.y, minCoords.z);
            // glVertex3f(minCoords.x, minCoords.y, maxCoords.z);
            // glVertex3f(minCoords.x, maxCoords.y, maxCoords.z);
            // glVertex3f(minCoords.x, maxCoords.y, minCoords.z);

            // glNormal3f(1, 0, 0);
            // glVertex3f(maxCoords.x, minCoords.y, minCoords.z);
            // glVertex3f(maxCoords.x, minCoords.y, maxCoords.z);
            // glVertex3f(maxCoords.x, maxCoords.y, maxCoords.z);
            // glVertex3f(maxCoords.x, maxCoords.y, minCoords.z);

            // glNormal3f(0, -1, 0);
            // glVertex3f(minCoords.x, minCoords.y, minCoords.z);
            // glVertex3f(minCoords.x, minCoords.y, maxCoords.z);
            // glVertex3f(maxCoords.x, minCoords.y, maxCoords.z);
            // glVertex3f(maxCoords.x, minCoords.y, minCoords.z);

            // glNormal3f(0, 1, 0);
            // glVertex3f(minCoords.x, maxCoords.y, minCoords.z);
            // glVertex3f(minCoords.x, maxCoords.y, maxCoords.z);
            // glVertex3f(maxCoords.x, maxCoords.y, maxCoords.z);
            // glVertex3f(maxCoords.x, maxCoords.y, minCoords.z);
    }

    static std::tuple<float, float, float> getColor(unsigned int id)
    {
        id += 5;
        float color[3] = {0.f, 0.f, 0.f};

        constexpr unsigned int NB_CUBE_TRANSITION = 3; //nb cubes necessary to change color (rgb)
        constexpr unsigned int NB_COLOR = 3;

        int index = (id / (NB_CUBE_TRANSITION*2)) % NB_COLOR;

        if (id % (NB_CUBE_TRANSITION * 2) < NB_CUBE_TRANSITION)
            color[index] = float((id % NB_CUBE_TRANSITION)) / float(NB_CUBE_TRANSITION);
        else 
            color[index] = 1 - (id % NB_CUBE_TRANSITION) / float(NB_CUBE_TRANSITION);

        return std::make_tuple(color[0], color[1], color[2]);
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
        Mesh m;
        Construct::UVSphere(50,50,m);
        GLfloat specular2[4] = {0.9,0.9,0.9,1};
        //glLightfv(GL_LIGHT0, GL_SPECULAR, specular2);
        //glColorMaterial(GL_FRONT, GL_AMBIENT);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular2);
        GLfloat r[4];
        glGetMaterialfv(GL_FRONT, GL_SPECULAR, r);
        float gdr = 2;
        glMaterialfv(GL_FRONT, GL_SHININESS, &gdr);
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
        for (unsigned int ki = 0; ki < 4; ki++)
            std::cout << (float)r[ki] << std::endl;

        glBegin(GL_QUADS);
        unsigned int n = (nbCubes < TOWER_MAX_SIZE ? nbCubes : TOWER_MAX_SIZE);
        for (unsigned int i = 0; i < n; i++)
        {
            //float f = float(i) / float(n);
            //glColor3f(0, f, 0);
            //float* rgb = S_Cube::getColor(i);
            float rgb[3];// = {1.f, 1.f, 1.f};
            std::tie(rgb[0], rgb[1], rgb[2]) = S_Cube::getColor(i);
            glColor3f(rgb[0], rgb[1], rgb[2]);
            cubes[i].draw();
        }
        glEnd();

        //m.draw();
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