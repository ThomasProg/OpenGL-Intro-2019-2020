#ifndef _REFERENTIAL_H_
#define _REFERENTIAL_H_

#include "macros.h"
//#include "cone.h"

void drawRef()
{
    constexpr unsigned int precision = 10;

    glBegin(GL_LINES);

    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(0, 0, 0);
    glVertex3f(2.f, 0, 0);

    glColor3f(0.f, 1.f, 0.f);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 2.f, 0);

    glColor3f(0.f, 0.f, 1.f);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 2.f);

    glEnd();

    // {
    //     glPushMatrix();

    //     glTranslatef(1.8f, 0.f, 0.f);
    //     glScalef(0.2, 0.05, 0.05);
    //     glRotatef(90.f, 0.f, 1.f, 0.f);
    //     Mesh cone;
    //     cone.bDraw = false;
    //     glColor3f(1.f, 0.f, 0.f);
    //     drawCone(precision, cone);
    //     glPopMatrix();
    // }

    // {
    //     glPushMatrix();
    //     glTranslatef(0.f, 1.8f, 0.f);
    //     glScalef(0.05, 0.2, 0.05);
    //     glRotatef(-90.f, 1, 0, 0);
    //     Mesh cone;
    //     cone.bDraw = false;
    //     glColor3f(0.f, 1.f, 0.f);
    //     drawCone(precision, cone);
    //     glPopMatrix();
    // }

    // {
    //     glPushMatrix();
    //     glTranslatef(0.f, 0.f, 1.8f);
    //     glScalef(0.05, 0.05, 0.2);
    //     Mesh cone;
    //     cone.bDraw = false;
    //     glColor3f(0.f, 0.f, 1.f);
    //     drawCone(precision, cone);
    //     glPopMatrix();
    // }
}

#endif