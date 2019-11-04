#ifndef _CUBE_H_
#define _CUBE_H_

#include "macros.h"

void drawCube()
{
    //glBegin(GL_TRIANGLE_STRIP);
    glBegin(GL_LINE_STRIP);

    glColor3f(0xFF, 0x00, 0x00);
    glVertex3f(- SHAPE_SCREEN_SIZE_X / 2, - SHAPE_SCREEN_SIZE_Y / 2, - SHAPE_SCREEN_SIZE_Z / 2);
    glVertex3f(+ SHAPE_SCREEN_SIZE_X / 2, - SHAPE_SCREEN_SIZE_Y / 2, - SHAPE_SCREEN_SIZE_Z / 2);

    glVertex3f(- SHAPE_SCREEN_SIZE_X / 2, + SHAPE_SCREEN_SIZE_Y / 2, - SHAPE_SCREEN_SIZE_Z / 2);
    glVertex3f(+ SHAPE_SCREEN_SIZE_X / 2, + SHAPE_SCREEN_SIZE_Y / 2, - SHAPE_SCREEN_SIZE_Z / 2);

    glColor3f(0xFF, 0x55, 0x55);

    glVertex3f(- SHAPE_SCREEN_SIZE_X / 2, + SHAPE_SCREEN_SIZE_Y / 2, + SHAPE_SCREEN_SIZE_Z / 2);
    glVertex3f(+ SHAPE_SCREEN_SIZE_X / 2, + SHAPE_SCREEN_SIZE_Y / 2, + SHAPE_SCREEN_SIZE_Z / 2);
    // glVertex3f(- SHAPE_SCREEN_SIZE_X / 2, + SHAPE_SCREEN_SIZE_Y / 2, + SHAPE_SCREEN_SIZE_Z / 2);
    // glVertex3f(+ SHAPE_SCREEN_SIZE_X / 2, + SHAPE_SCREEN_SIZE_Y / 2, + SHAPE_SCREEN_SIZE_Z / 2);
    //glColor3f(0x00, 0x00, 0x00);
    glVertex3f(- SHAPE_SCREEN_SIZE_X / 2, - SHAPE_SCREEN_SIZE_Y / 2, + SHAPE_SCREEN_SIZE_Z / 2);
    glVertex3f(+ SHAPE_SCREEN_SIZE_X / 2, - SHAPE_SCREEN_SIZE_Y / 2, + SHAPE_SCREEN_SIZE_Z / 2);



    glEnd();
}

#endif