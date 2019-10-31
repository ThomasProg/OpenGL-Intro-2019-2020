#include <cstdio>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>

#define PI 3.14

constexpr int SCREEN_WIDTH  = 1280;
constexpr int SCREEN_HEIGHT =  700;
constexpr float SPEED = 0.05f;
constexpr float SHAPE_SIZE = 200;

constexpr float SHAPE_SCREEN_SIZE_X = SHAPE_SIZE / SCREEN_WIDTH;
constexpr float SHAPE_SCREEN_SIZE_Y = SHAPE_SIZE / SCREEN_HEIGHT;
constexpr float SHAPE_SCREEN_SIZE_Z = SHAPE_SIZE / SCREEN_HEIGHT;

constexpr float h = -0.2f;

#define X .525731112119133606 
#define Z .850650808352039932

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

void drawSphere2()
{
    static GLfloat vdata[12][3] = {    
    {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},    
    {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},    
    {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0} 
    };
    static GLuint tindices[20][3] = { 
    {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},    
    {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},    
    {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6}, 
    {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };
    int i;
    
    glBegin(GL_TRIANGLES);    
    for (i = 0; i < 20; i++) {    
    /* color information here */ 
    glVertex3fv(&vdata[tindices[i][0]][0]); 
    glVertex3fv(&vdata[tindices[i][1]][0]); 
    glVertex3fv(&vdata[tindices[i][2]][0]); 
    }
    glEnd();
}

void drawSphere(unsigned int nbPoints = 10, GLenum drawMode = GL_TRIANGLE_FAN, float x = 0, float y = 0, float z = 0)
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

    glBegin(drawMode);
    for (unsigned int i = 0; i < nbPoints; i++)
    {
        glVertex3f(0.f,
                   SHAPE_SIZE * (cos(rotPerPoint * i)) / SCREEN_WIDTH + x, 
                   SHAPE_SIZE * (sin(rotPerPoint * i)) / SCREEN_HEIGHT + y);
    }
    glEnd();
}

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

    glColor3f(0xFF, 0x00, 0x00);

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

void drawCone(unsigned int nbPoints, GLenum drawMode = GL_TRIANGLE_FAN, 
            float x = 0, float y = 0, float z = 0, 
            float scaleX = 1, float scaleY = 1, float scaleZ = 1)
{
    nbPoints--;

    float px[nbPoints], py[nbPoints];

    glBegin(drawMode);

    const float rotPerPoint = 2*PI/nbPoints;
    for (unsigned int i = 0; i < nbPoints; i++)
    {
        px[i] = scaleX * SHAPE_SIZE * (cos(rotPerPoint * i)) / SCREEN_WIDTH + x;
        py[i] = scaleY * SHAPE_SIZE * (sin(rotPerPoint * i)) / SCREEN_HEIGHT + y;

        glVertex3f(px[i], 
                   py[i], 
                   scaleZ * z);
    }

    glEnd();

    glColor3f(0xFF, 0x00, 0x00);

    if (drawMode == GL_TRIANGLE_FAN)
        glBegin(GL_TRIANGLE_STRIP);
    else
        glBegin(GL_LINES);

    for (unsigned int i = 0; i < nbPoints; i++)
    {
        glVertex3f(px[i], 
                   py[i], 
                   scaleZ * z);
        // glVertex3f((x + px[i])/2, 
        //            (y + py[i])/2, 
        //            -1);
        glVertex3f(x, 
                   y, 
                   scaleZ * (h + z));

        // glVertex3f(0, 
        //            0, 
        //            -1);
    }

    glVertex3f(px[0], 
                py[0], 
                scaleZ * z);
    glVertex3f(x, 
                y, 
                scaleZ * (h + z));
    // glVertex3f(0, 
    //             0, 
    //             -1);

    glEnd();
}

void drawCone2(unsigned int nbPoints, GLenum drawMode = GL_TRIANGLE_FAN, float x = 0, float y = 0, float z = 0)
{
    drawConeCut(nbPoints, drawMode, x, y, z);
    drawCone(nbPoints, drawMode, x, y, z + 2 * h, 0.5, 0.5, 0.5);
}

void moveShape(GLFWwindow* window, float& locX, float& locY)
{
    if (glfwGetKey(window, GLFW_KEY_RIGHT))
    {
        locX += SPEED;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT))
    {
        locX -= SPEED;
    }
    if (glfwGetKey(window, GLFW_KEY_UP))
    {
        locY += SPEED;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN))
    {
        locY -= SPEED;
    }
}

void updateColor(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT))
    {
        if (glfwGetKey(window, GLFW_KEY_R))
            glClearColor(0xFF, 0x00, 0x00, 0xFF);

        if (glfwGetKey(window, GLFW_KEY_G))
            glClearColor(0x00, 0xFF, 0x00, 0xFF);

        if (glfwGetKey(window, GLFW_KEY_B))
        {
            glClearColor(0x00, 0x00, 0xFF, 0xFF);
        }
    }
    else
    {
        if (glfwGetKey(window, GLFW_KEY_R))
            glColor3f(0xFF, 0x00, 0x00);

        if (glfwGetKey(window, GLFW_KEY_G))
            glColor3f(0x00, 0xFF, 0x00);

        if (glfwGetKey(window, GLFW_KEY_B))
            glColor3f(0x00, 0x00, 0xFF);
    }
}

void drawShapes(GLFWwindow* window, GLenum drawMode = GL_TRIANGLE_FAN, float locX = 0, float locY = 0, float locZ = 0)
{
    drawCube();
    //drawSphere();
    //drawSphere2();
    glRotated(0.5, 1, 0.0, 0.0);

    if (glfwGetKey(window, GLFW_KEY_3))
    {
        glBegin(GL_LINES);

        glVertex3f(locX, locY, locZ);
        glVertex3f(locX, 100 + locY, locZ);

        glVertex3f(locX, locY, locZ);
        glVertex3f(100 + locX, locY, locZ);

        glVertex3f(locX, locY, locZ);
        glVertex3f(locX, locY, 100 + locZ);

        glEnd();
    }

    if (glfwGetKey(window, GLFW_KEY_4))
    {
        drawCone(4, drawMode, locX, locY);
    }

    if (glfwGetKey(window, GLFW_KEY_5))
    {
        drawCone(5, drawMode, locX, locY);
    }

    if (glfwGetKey(window, GLFW_KEY_6))
    {
        drawCone(6, drawMode, locX, locY);
    }

    if (glfwGetKey(window, GLFW_KEY_7))
    {
        drawCone(7, drawMode, locX, locY);
    }

    if (glfwGetKey(window, GLFW_KEY_8))
    {
        drawCone(8, drawMode, locX, locY);
    }

    if (glfwGetKey(window, GLFW_KEY_9))
    {
        drawCone(9, drawMode, locX, locY);
    }

    if (glfwGetKey(window, GLFW_KEY_0))
    {
        drawCone(200, drawMode, locX, locY);
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main()
{
    if (!glfwInit())
    {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);


    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "hello world", NULL, NULL);

    glfwMakeContextCurrent(window);

    if (!gladLoadGL())
    {
        glfwTerminate();
        return -1;
    }

    bool bFillShape = true;
    bool bMinusInput = false;
    float locX = 0, locY = 0;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.5f, 0.5f, 0.5f, 1.f);
        glColor3f(0xFF, 0xFF, 0xFF);

        moveShape(window, locX, locY);

        updateColor(window);

        if (glfwGetKey(window, GLFW_KEY_MINUS) && glfwGetKey(window, GLFW_KEY_MINUS) != bMinusInput)
        {
            bFillShape = !bFillShape; 
            bMinusInput =  true;
        }
        else if (!glfwGetKey(window, GLFW_KEY_MINUS))
            bMinusInput = false;

        GLenum drawMode = bFillShape ? GL_LINE_LOOP : GL_TRIANGLE_FAN;

        drawShapes(window, drawMode, locX, locY);

        glfwSwapBuffers(window);
    }

    glfwTerminate();

}