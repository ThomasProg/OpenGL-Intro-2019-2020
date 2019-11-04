#include <cstdio>

#include "macros.h"
#include "mesh.h"
#include "sphere.h"
#include "cone.h"
#include "cube.h"
#include "referential.h"
#include "doOnce.h"

constexpr float rotationSpeed = 0.5f;
constexpr float scaleSpeed = 1.f / 10.f;

struct S_Inputs
{
    S_DoOnce scaleSubstract;
    S_DoOnce scaleAdd;
    S_DoOnce x;
    S_DoOnce y;
    S_DoOnce z;

    S_DoOnce showEdges;
};

void moveShape(GLFWwindow* window, S_Inputs& inputs)
{
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT))
    {
        if (glfwGetKey(window, GLFW_KEY_RIGHT))
        {
            glTranslated(1/100.0, 0, 0.0);
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT))
        {
            glTranslated(-1.0/100, 0, 0.0);
        }
        if (glfwGetKey(window, GLFW_KEY_UP))
        {
            glTranslated(0.0, 0, 1/100);
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN))
        {
            glTranslated(0.0, 0, -1/100);
        }
    }

    inputs.x.input(glfwGetKey(window, GLFW_KEY_X));
    if (inputs.x.isOn)
        glRotated(rotationSpeed, 1.f, 0.f, 0.f);

    inputs.y.input(glfwGetKey(window, GLFW_KEY_Y));
    if (inputs.y.isOn)
        glRotated(rotationSpeed, 0.f, 1.f, 0.f);
    
    inputs.z.input(glfwGetKey(window, GLFW_KEY_Z));
    if (inputs.z.isOn)
        glRotated(rotationSpeed, 0.f, 0.f, 1.f);
    

    if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) || glfwGetKey(window, GLFW_KEY_MINUS))
        glScalef(1.f - scaleSpeed, 1.f - scaleSpeed, 1.f - scaleSpeed);
    if (glfwGetKey(window, GLFW_KEY_KP_ADD)  || glfwGetKey(window, GLFW_KEY_EQUAL))
        glScalef(1.f + scaleSpeed, 1.f + scaleSpeed, 1.f + scaleSpeed);
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

void drawShapes(GLFWwindow* window, GLenum drawMode = GL_TRIANGLE_FAN, bool showEdges = false)
{
    //drawCube();

    Mesh mesh;
    mesh.drawMode = drawMode;

    if (glfwGetKey(window, GLFW_KEY_1))
    {
        //sphere.bDraw = true;
        UVSphere(100, 100, mesh);
        mesh.draw();
    }

    if (glfwGetKey(window, GLFW_KEY_2))
    {
        drawCube(showEdges);
    }

    if (glfwGetKey(window, GLFW_KEY_3))
    {
        drawRef();
    }

    if (glfwGetKey(window, GLFW_KEY_4))
    {
        drawCone(4, mesh);
    }

    if (glfwGetKey(window, GLFW_KEY_5))
    {
        drawCone(5, mesh);
    }

    if (glfwGetKey(window, GLFW_KEY_6))
    {
        drawCone(6, mesh);
    }

    if (glfwGetKey(window, GLFW_KEY_7))
    {
        drawCone(7, mesh);
    }

    if (glfwGetKey(window, GLFW_KEY_8))
    {
        drawCone(8, mesh);
    }

    if (glfwGetKey(window, GLFW_KEY_9))
    {
        drawCone(9, mesh);
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


    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Geometry", NULL, NULL);

    glfwMakeContextCurrent(window);

    if (!gladLoadGL())
    {
        glfwTerminate();
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    glScalef(600.f / float(SCREEN_HEIGHT), 600.f / float(SCREEN_WIDTH), 600.f / float(SCREEN_HEIGHT));

    S_Inputs inputs;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glClearColor(0.5f, 0.5f, 0.5f, 1.f);
        glColor3f(0xFF, 0xFF, 0xFF);

        moveShape(window, inputs);

        updateColor(window);

        inputs.showEdges.input(glfwGetKey(window, GLFW_KEY_M));

        GLenum drawMode = inputs.showEdges.isOn ? GL_LINE_LOOP : GL_TRIANGLE_FAN;

        drawShapes(window, drawMode, inputs.showEdges.isOn);

        glfwSwapBuffers(window);
    }

    glfwTerminate();

}