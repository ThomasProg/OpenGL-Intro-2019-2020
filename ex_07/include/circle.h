#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "macros.h"

void drawCircle(unsigned int nbPoints, GLenum drawMode = GL_TRIANGLE_FAN, float x = 0, float y = 0)
{
    glBegin(drawMode);
    const float rotPerPoint = 2*PI/nbPoints;
    for (unsigned int i = 0; i < nbPoints; i++)
    {
        glVertex3f(SHAPE_SIZE * (cos(rotPerPoint * i)) / SCREEN_WIDTH + x, 
                   SHAPE_SIZE * (sin(rotPerPoint * i)) / SCREEN_HEIGHT + y, 
                   0.f);
    }
    glEnd();
}

#endif