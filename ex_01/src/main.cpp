#include <cstdio>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>

#define PI 3.14

constexpr int SCREEN_WIDTH  = 1280;
constexpr int SCREEN_HEIGHT =  700;
constexpr float SPEED = 0.01f;
constexpr float SHAPE_SIZE = 600;

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

void moveShape(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_RIGHT))
        glTranslatef(SPEED, 0, 0);
    if (glfwGetKey(window, GLFW_KEY_LEFT))
        glTranslatef(-SPEED, 0, 0);
    if (glfwGetKey(window, GLFW_KEY_UP))
        glTranslatef(0, SPEED, 0);
    if (glfwGetKey(window, GLFW_KEY_DOWN))
        glTranslatef(0, - SPEED, 0);
}

void updateColor(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT))
    {
        //set background color
        if (glfwGetKey(window, GLFW_KEY_R))
            glClearColor(0xFF, 0x00, 0x00, 0xFF);

        if (glfwGetKey(window, GLFW_KEY_G))
            glClearColor(0x00, 0xFF, 0x00, 0xFF);

        if (glfwGetKey(window, GLFW_KEY_B))
            glClearColor(0x00, 0x00, 0xFF, 0xFF);
    }
    else
    {
        //set shape color
        if (glfwGetKey(window, GLFW_KEY_R))
            glColor3f(0xFF, 0x00, 0x00);

        if (glfwGetKey(window, GLFW_KEY_G))
            glColor3f(0x00, 0xFF, 0x00);

        if (glfwGetKey(window, GLFW_KEY_B))
            glColor3f(0x00, 0x00, 0xFF);
    }
}

void drawShapes(GLFWwindow* window, bool bFillShape)//GLenum drawMode = GL_TRIANGLE_FAN)
{
    if (glfwGetKey(window, GLFW_KEY_1))
    {
        glBegin(GL_POINTS);
    
        glVertex3f(0.f, 0.f, 0.f);

        glEnd();
    }

    if (glfwGetKey(window, GLFW_KEY_2))
    {
        glBegin(GL_LINES);

        glVertex3f(0.f, 0.f, 0.0f);
        glVertex3f(0.25f, 0.25f, 0.f);

        glEnd();
    }

    if (glfwGetKey(window, GLFW_KEY_3))
        drawCircle(3, bFillShape);

    if (glfwGetKey(window, GLFW_KEY_4))
        drawCircle(4, bFillShape);

    if (glfwGetKey(window, GLFW_KEY_5))
        drawCircle(5, bFillShape);

    if (glfwGetKey(window, GLFW_KEY_6))
        drawCircle(6, bFillShape);

    if (glfwGetKey(window, GLFW_KEY_7))
        drawCircle(7, bFillShape);

    if (glfwGetKey(window, GLFW_KEY_8))
        drawCircle(8, bFillShape);

    if (glfwGetKey(window, GLFW_KEY_9))
        drawCircle(9, bFillShape);

    if (glfwGetKey(window, GLFW_KEY_0))
        drawCircle(200, bFillShape);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
    if (!glfwInit())
    {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Opengl Shapes 2D", NULL, NULL);

    glfwMakeContextCurrent(window);

    if (!gladLoadGL())
    {
        glfwTerminate();
        return -1;
    }

    //doOnce booleans
    bool bFillShape = true;
    bool bMinusInput = false;

    //relative to Window
    glScalef(SHAPE_SIZE / float(SCREEN_WIDTH), 
             SHAPE_SIZE / float(SCREEN_HEIGHT), 
             SHAPE_SIZE / float(SCREEN_WIDTH));

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.f);
        glColor3f(0xFF, 0xFF, 0xFF);

        moveShape(window);

        updateColor(window);

        //do once per click struct
        if (glfwGetKey(window, GLFW_KEY_MINUS) && glfwGetKey(window, GLFW_KEY_MINUS) != bMinusInput)
        {
            bFillShape = !bFillShape; 
            bMinusInput =  true;
        }
        else if (!glfwGetKey(window, GLFW_KEY_MINUS))
            bMinusInput = false;

        drawShapes(window, bFillShape);

        glfwSwapBuffers(window);
    }

    glfwTerminate();

}