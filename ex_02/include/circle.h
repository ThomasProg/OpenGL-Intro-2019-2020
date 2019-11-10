#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "macros.h"

void drawCircle(unsigned int nbPoints, bool bFillShape = true)
{
    if (bFillShape)
        glBegin(GL_TRIANGLE_FAN);
    else
        glBegin(GL_LINE_LOOP);
    const float rotPerPoint = 2*PI/nbPoints;
    for (unsigned int i = 0; i < nbPoints; i++)
    {
        glVertex3f(cos(rotPerPoint * i), 
                   sin(rotPerPoint * i), 
                   0.f);
    }
    glEnd();
}
#endif