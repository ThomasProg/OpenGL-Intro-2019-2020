#ifndef _CONE_H_
#define _CONE_H_

#include "macros.h"
#include "mesh.h"

constexpr float h = 1.f;

//cut 
void drawConeCut(unsigned int nbPoints, GLenum drawMode = GL_TRIANGLE_FAN, float x = 0, float y = 0, float z = 0)
{
    nbPoints--;

    float px[nbPoints], py[nbPoints];

    glBegin(drawMode);

    const float rotPerPoint = 2*PI/nbPoints;
    for (unsigned int i = 0; i < nbPoints; i++)
    {
        px[i] = SHAPE_SIZE * (cos(rotPerPoint * i)) / SCREEN_WIDTH + x;
        py[i] = SHAPE_SIZE * (sin(rotPerPoint * i)) / SCREEN_HEIGHT + y;

        glVertex3f(px[i], 
                   py[i], 
                   z);
    }

    glEnd();

    if (drawMode == GL_TRIANGLE_FAN)
        glBegin(GL_TRIANGLE_STRIP);
    else
        glBegin(GL_LINES);

    for (unsigned int i = 0; i < nbPoints; i++)
    {
        glVertex3f(px[i], 
                   py[i], 
                   z);
        glVertex3f((x + px[i])/2, 
                   (y + py[i])/2, 
                   h + z);
    }

    glVertex3f(px[0], 
                py[0], 
                z);
    glVertex3f(x + px[0]/2, 
                y + py[0]/2, 
                h + z);

    glEnd();
}

void drawCone(unsigned int nbPoints, Mesh& mesh) 
{
    //if (mesh.drawMode == GL_TRIANGLE_FAN)
    if (mesh.bShowEdges)
        glBegin(GL_TRIANGLE_FAN);
    else
        glBegin(GL_LINE_LOOP);

    GLenum drawMode;// = mesh.drawMode;
    if (mesh.bShowEdges)
        drawMode = GL_TRIANGLE_FAN;
    else 
        drawMode = GL_LINE_LOOP;
    // double& x = mesh.relativeLoc.x;
    // double& y = mesh.relativeLoc.y;
    // double& z = mesh.relativeLoc.z;
    // double& scaleX = mesh.relativeScale.x;
    // double& scaleY = mesh.relativeScale.y;
    // double& scaleZ = mesh.relativeScale.z;

    nbPoints--;

    float px[nbPoints], py[nbPoints];

    //glBegin(drawMode);
    //glBegin(GL_TRIANGLE_FAN);

    const float rotPerPoint = 2*PI/nbPoints;
    for (unsigned int i = 0; i < nbPoints; i++)
    {
        px[i] = cos(rotPerPoint * i);
        py[i] = sin(rotPerPoint * i);

        //mesh.color(px[i], py[i], scaleZ * z);
        glVertex3f(px[i], 
                   py[i], 
                   0);
    }

    glEnd();

    //glColor3f(0xFF, 0x00, 0x00);

    if (drawMode == GL_TRIANGLE_FAN)
        glBegin(GL_TRIANGLE_STRIP);
    else
        glBegin(GL_LINES);

    for (unsigned int i = 0; i < nbPoints; i++)
    {
        mesh.color(px[i], py[i], 0);
        glVertex3f(px[i], 
                   py[i], 
                   0);

        mesh.color(0, 0, h);
        glVertex3f(0, 
                   0, 
                   h);

    }

    glVertex3f(px[0], 
                py[0], 
                0);
    glVertex3f(0, 
                0, 
                h);

    glEnd();
}

void drawCone2(unsigned int nbPoints, GLenum drawMode = GL_TRIANGLE_FAN, float x = 0, float y = 0, float z = 0)
{
    // Mesh mesh;
    // mesh.drawMode = drawMode;
    // drawConeCut(nbPoints, drawMode, x, y, z);
    // drawCone(nbPoints, drawMode, x, y, z + 2 * h, 0.5, 0.5, 0.5);
}

#endif