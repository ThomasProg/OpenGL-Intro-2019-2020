#ifndef _CUBE_H_
#define _CUBE_H_

#include "macros.h"
#include "mesh.h"

void addTriangle(const Vector3& v1, const Vector3& v2, const Vector3& v3)
{
    glColor3f(0xFF, 0x00, 0x00);
    glVertex3f(v1.x, v1.y, v1.z);

    glColor3f(0x00, 0xFF, 0x00);
    glVertex3f(v2.x, v2.y, v2.z);

    glColor3f(0x00, 0x00, 0xFF);
    glVertex3f(v3.x, v3.y, v3.z);
}

void addQuad(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& v4)
{
    addTriangle(v1, v2, v3);
    addTriangle(v1, v3, v4);
}

void drawCube(bool showEdges)
{
    if (showEdges)
        glBegin(GL_LINE_LOOP);
    else 
        glBegin(GL_TRIANGLES);

    for (int i = -1; i < 2; i += 2)
    {
        addQuad(
            Vector3(i, -1, -1), 
            Vector3(i, -1, 1), 
            Vector3(i, 1, 1),
            Vector3(i, 1, -1));

        addQuad(
            Vector3(-1, i, -1), 
            Vector3(-1, i, 1), 
            Vector3(1, i, 1),
            Vector3(1, i, -1));

        addQuad(
            Vector3(-1, -1, i), 
            Vector3(-1, 1, i), 
            Vector3(1, 1, i),
            Vector3(1, -1, i));
    }

    glEnd();
}

#endif