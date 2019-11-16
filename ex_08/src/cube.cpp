#include "cube.h"

S_Cube S_Cube::cutBy(const S_Cube& edges)
{
    minCoords.x = std::max(minCoords.x, edges.minCoords.x); 
    minCoords.z = std::max(minCoords.z, edges.minCoords.z); 
    maxCoords.x = std::min(maxCoords.x, edges.maxCoords.x); 
    maxCoords.z = std::min(maxCoords.z, edges.maxCoords.z); 

    return *this;
}

bool S_Cube::isInRange(const S_Cube& cube) const
{
    return minCoords.x <= cube.maxCoords.x && maxCoords.x >= cube.minCoords.x
        && minCoords.z <= cube.maxCoords.z && maxCoords.z >= cube.minCoords.z;
}


//O(n^3) complexity
//could be optimized : 
// - to O(6 * n^2) complexity
// - reduce glVertex3f call number
void S_Cube::draw() const
{
    //cube subdivided to give specular effect on materials
    constexpr unsigned int nbDivisions = 5;
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

                //draw faces
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
}

std::tuple<float, float, float> S_Cube::getColor(unsigned int id)
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

void S_Cube::moveAxis(float& center, float& min, float& max, float alpha)
{
    float delta = center;
    center      = std::sin(alpha * moveSpeed) * moveDistance;
    delta      -= center;

    max -= delta;
    min -= delta;
}

void S_Cube::movingCubeTick(bool axisIsX, float currentTime)
{
    //move cube
    if (axisIsX)
        moveAxis(startCenter.x, minCoords.x, maxCoords.x, currentTime);
    else 
        moveAxis(startCenter.z, minCoords.z, maxCoords.z, currentTime);

    glBegin(GL_QUADS);
    draw();
    glEnd();
}
