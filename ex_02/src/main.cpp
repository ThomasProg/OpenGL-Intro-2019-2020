#include <cstdio>

#include "macros.h"
#include "mesh.h"
#include "sphere.h"
#include "cone.h"

void moveShape(GLFWwindow* window)
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
    else 
    {
        if (glfwGetKey(window, GLFW_KEY_RIGHT))
        {
            glRotated(0.5, 0, 1.0, 0.0);
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT))
        {
            glRotated(0.5, 0, -1.0, 0.0);
        }
        if (glfwGetKey(window, GLFW_KEY_UP))
        {
            glRotated(0.5, 1, 0.0, 0);
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN))
        {
            glRotated(0.5, -1, 0.0, 0);
        }
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

void drawShapes(GLFWwindow* window, GLenum drawMode = GL_TRIANGLE_FAN)
{
    if (glfwGetKey(window, GLFW_KEY_3))
    {
        glBegin(GL_LINES);

        glVertex3f(0, 0, 0);
        glVertex3f(0, 1, 0);

        glVertex3f(0, 0, 0);
        glVertex3f(1, 0, 0);

        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 1);

        glEnd();
    }

    Mesh mesh;
    mesh.drawMode = drawMode;

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

    if (glfwGetKey(window, GLFW_KEY_0))
    {
        //sphere.bDraw = true;
        UVSphere(100, 100, mesh);
        mesh.draw();
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

    bool bFillShape = true;
    bool bMinusInput = false;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.5f, 0.5f, 0.5f, 1.f);
        glColor3f(0xFF, 0xFF, 0xFF);

        moveShape(window);

        updateColor(window);

        if (glfwGetKey(window, GLFW_KEY_MINUS) && glfwGetKey(window, GLFW_KEY_MINUS) != bMinusInput)
        {
            bFillShape = !bFillShape; 
            bMinusInput =  true;
        }
        else if (!glfwGetKey(window, GLFW_KEY_MINUS))
            bMinusInput = false;

        GLenum drawMode = bFillShape ? GL_LINE_LOOP : GL_TRIANGLE_FAN;

        drawShapes(window, drawMode);

        glfwSwapBuffers(window);
    }

    glfwTerminate();

}