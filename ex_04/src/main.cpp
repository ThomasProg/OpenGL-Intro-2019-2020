#include <cstdio>

#include "macros.h"
#include "mesh.h"
#include "sphere.h"
#include "cone.h"
#include "cube.h"
#include "referential.h"
#include "doOnce.h"
#include "utilities.h"

constexpr float rotationSpeed = 0.5f;
constexpr float scaleSpeed = 1.f / 10.f;

struct S_Inputs
{
    S_DoOnce scaleSubstract;
    S_DoOnce scaleAdd;
    S_DoOnce x;
    S_DoOnce y;
    S_DoOnce z;

    S_DoOnce rightMouseClick;
    S_DoOnce leftMouseClick;

    S_DoOnce showEdges;
};

void moveShape(GLFWwindow* window, S_Inputs& inputs, Mesh& mesh)
{
    inputs.x.input(glfwGetKey(window, GLFW_KEY_X));
    if (inputs.x.isOn)
    {
        //glRotated(rotationSpeed, 1.f, 0.f, 0.f);
        mesh.rotation.x+=1.f;
    }

    inputs.y.input(glfwGetKey(window, GLFW_KEY_Y));
    if (inputs.y.isOn)
    {
        //glRotated(rotationSpeed, 0.f, 1.f, 0.f);
        mesh.rotation.y += 1.f;
    }
    
    inputs.z.input(glfwGetKey(window, GLFW_KEY_Z));
    if (inputs.z.isOn)
    {
        //glRotated(rotationSpeed, 0.f, 0.f, 1.f);
        mesh.rotation.z += 1.f;
    }
    
    if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) || glfwGetKey(window, GLFW_KEY_MINUS))
    {
        //glScalef(1.f - scaleSpeed, 1.f - scaleSpeed, 1.f - scaleSpeed);
        mesh.scale.x *= 1.f - scaleSpeed;
        mesh.scale.y *= 1.f - scaleSpeed;
        mesh.scale.z *= 1.f - scaleSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_KP_ADD)  || glfwGetKey(window, GLFW_KEY_EQUAL))
    {
        //glScalef(1.f + scaleSpeed, 1.f + scaleSpeed, 1.f + scaleSpeed);
        mesh.scale.x *= 1.f + scaleSpeed;
        mesh.scale.y *= 1.f + scaleSpeed;
        mesh.scale.z *= 1.f + scaleSpeed;
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

void drawShapes(GLFWwindow* window, Mesh& mesh, bool showEdges = false)
{
    //drawCube();

    if (glfwGetKey(window, GLFW_KEY_1))
    {
        //sphere.bDraw = true;
        //if (!mesh.bIsSphere)
        //{
        //Construct::UVSphere(30, 30, mesh);
        mesh.set(E_MeshType::E_SPHERE);
        //    mesh.bIsSphere = true;
        //}
        mesh.draw();
    }

    if (glfwGetKey(window, GLFW_KEY_2))
    {
        mesh.set(E_MeshType::E_CUBE);
        mesh.draw();
        //drawCube(showEdges);
        //Construct::cube(mesh);
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

struct vec2
{
    double x, y;
    vec2(double x, double y) : x(x), y(y) {}
    vec2 operator-(const vec2& v)
    {
        return vec2(x-v.x, y - v.y);
    }
    vec2 operator+(const vec2& v)
    {
        return vec2(x+v.x, y + v.y);
    }
    double length()
    {
        return sqrt(pow(x,2) + pow(y,2));
    }
    vec2 unit()
    {
        double len = length();
        if (len == 0)
            return vec2(1,0); 
        else
            return vec2(x/len, y/len);
    }
};

struct S_Path
{
    std::vector<vec2> points;
    bool bIsOpen = false;

    void addPoint(GLFWwindow* window)
    {
        if (bIsOpen)
        {
            bIsOpen = false;
            points.clear();
        }

        double x, y;
        glfwGetCursorPos(window, &x, &y);

        x -= double(SCREEN_WIDTH)/2.0;
        y -= double(SCREEN_HEIGHT)/2.0;

        x /= double(SCREEN_WIDTH);
        y /= double(SCREEN_HEIGHT);

        x *= 2;
        y *= 2;

        // x -= 0.5f;
        // y -= 0.5f;
        // x -= 1.f;
        // y -= 1.f;
        y *= -1.f;

        points.push_back(vec2(x, y));
    }
};

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
    S_Path   path;

    Vector3 shapesLoc(0,0,0);
    unsigned int currentIntersectIndex = 0;
    //float shapeLocRatio = 0.f;

    Mesh mesh;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glClearColor(0.5f, 0.5f, 0.5f, 1.f);
        glColor3f(0xFF, 0xFF, 0xFF);

        updateColor(window);

        inputs.showEdges.input(glfwGetKey(window, GLFW_KEY_M));
        //mesh.drawMode = inputs.showEdges.isOn ? GL_LINE_LOOP : GL_TRIANGLE_FAN;
        mesh.bShowEdges = inputs.showEdges.isOn;

        inputs.leftMouseClick.input(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT));

        inputs.rightMouseClick.input(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT));

        inputs.leftMouseClick.onSwitch = [&]()
        {
                path.addPoint(window);
        };
        inputs.rightMouseClick.onSwitch = [&]()
        {
                path.addPoint(window);
                path.bIsOpen = true;
        };

        drawRef();

        if (path.bIsOpen)
        {
            glPushMatrix();
            glScalef(float(SCREEN_HEIGHT) / 600.f, float(SCREEN_WIDTH) / 600.f, float(SCREEN_HEIGHT) / 600.f);

            glBegin(GL_LINE_LOOP);
            for (unsigned int i = 0; i < path.points.size(); i++)
            {
                float ratio = float(i) / float(path.points.size());
                {
                    glColor4f(1.f - ratio, 0.f, ratio, ratio);
                    float x = path.points[i].x;
                    float y = path.points[i].y;
                    glVertex3f(x, y, 0);
                }
            }
            glEnd();
            glPopMatrix();
        }

        {
            if (path.points.size() != 0 && path.bIsOpen)
            {
                glPushMatrix();

                vec2 translation(0,0);
                translation.x = shapesLoc.x - path.points[(currentIntersectIndex + 1) % path.points.size()].x;
                translation.y = shapesLoc.y - path.points[(currentIntersectIndex + 1) % path.points.size()].y;

                unsigned int i = currentIntersectIndex;
                while (vec2(translation.x, translation.y).length() < 0.03 && (currentIntersectIndex + 1) % path.points.size() != i)
                {
                    currentIntersectIndex++;
                    currentIntersectIndex%= path.points.size();
                    translation.x = shapesLoc.x - path.points[(currentIntersectIndex + 1) % path.points.size()].x;
                    translation.y = shapesLoc.y - path.points[(currentIntersectIndex + 1) % path.points.size()].y;
                }
                translation = translation.unit();
                translation.x *= -0.01;
                translation.y *= -0.01;
                glTranslatef(shapesLoc.x + translation.x, shapesLoc.y + translation.y, 0);
                shapesLoc.x += translation.x;
                shapesLoc.y += translation.y;

                glScalef(0.1, 0.1, 0.1);
                moveShape(window, inputs, mesh);
                mesh.useTransform();
                // glTranslatef(mesh.location.x, mesh.location.y, mesh.location.z);
                // glScalef(mesh.scale.x, mesh.scale.y, mesh.scale.z);
                // glRotated(mesh.rotation.x, 1, 0, 0);
                // glRotated(mesh.rotation.y, 0, 1, 0);
                // glRotated(mesh.rotation.z, 0, 0, 1);

                drawShapes(window, mesh, inputs.showEdges.isOn);
                if (glfwGetKey(window, GLFW_KEY_3))
                    drawRef();

                glPopMatrix();
            }
        }

        glfwSwapBuffers(window);
    }

    glfwTerminate();

}