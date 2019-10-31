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

void drawShapes(GLFWwindow* window, GLenum drawMode = GL_TRIANGLE_FAN, float locX = 0, float locY = 0)
{
    if (glfwGetKey(window, GLFW_KEY_1))
    {
        glBegin(GL_POINTS);
    
        glVertex3f(locX, locY, 0.0f);

        glEnd();
    }

    if (glfwGetKey(window, GLFW_KEY_2))
    {
        glBegin(GL_LINES);
    
        // glVertex3f(locX + 0 / SCREEN_WIDTH, locY + 0 / SCREEN_HEIGHT, 0.0f);
        // glVertex3f(locX + 0 / SCREEN_WIDTH, locY + 100/ SCREEN_HEIGHT, 0.0f);

        glVertex3f(locX, locY, 0.0f);
        glVertex3f(locX, 100 + locY, 0.0f);

        glEnd();
    }

    if (glfwGetKey(window, GLFW_KEY_3))
    {
        glBegin(GL_TRIANGLES);
    
        drawCircle(3, drawMode, locX, locY);

        glEnd();
    }

    if (glfwGetKey(window, GLFW_KEY_4))
    {
        drawCircle(4, drawMode, locX, locY);
    }

    if (glfwGetKey(window, GLFW_KEY_5))
    {
        drawCircle(5, drawMode, locX, locY);
    }

    if (glfwGetKey(window, GLFW_KEY_6))
    {
        drawCircle(6, drawMode, locX, locY);
    }

    if (glfwGetKey(window, GLFW_KEY_7))
    {
        drawCircle(7, drawMode, locX, locY);
    }

    if (glfwGetKey(window, GLFW_KEY_8))
    {
        drawCircle(8, drawMode, locX, locY);
    }

    if (glfwGetKey(window, GLFW_KEY_9))
    {
        drawCircle(9, drawMode, locX, locY);
    }

    if (glfwGetKey(window, GLFW_KEY_0))
    {
        drawCircle(200, drawMode, locX, locY);
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