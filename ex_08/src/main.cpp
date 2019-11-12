#include <cstdio>

#include "macros.h"
#include "mesh.h"
#include "camera.h"
#include "movingCube.h"
#include "doOnce.h"

constexpr float rotationSpeed = 0.5f;
constexpr float scaleSpeed = 1.f / 10.f;

struct S_Inputs
{
    S_DoOnce put;
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

    //glScalef(600.f / float(SCREEN_HEIGHT), 600.f / float(SCREEN_WIDTH), 600.f / float(SCREEN_HEIGHT));

    //S_Path   path;

    Vector3 shapesLoc(0,0,0);
    //unsigned int currentIntersectIndex = 0;
    //float shapeLocRatio = 0.f;

    Camera mainCamera;
    mainCamera.transform.location.z = 1;
    CubeTower tower;
    S_Cube movingCube(vector3D(0, 0.f, 0), vector3D(CUBE_SIZE, CUBE_SIZE, CUBE_SIZE));
    movingCube.minCoords.y += 0.1;
    movingCube.maxCoords.y += 0.1;  
    S_Inputs inputs;
    mainCamera.transform.location.y += 0.1;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    double previousTime = glfwGetTime();
    glEnable(GL_FOG);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double time =  glfwGetTime();
        mainCamera.deltaTime = time - previousTime;
        //FPS
        //std::cout << "FPS : " << 1/(time - previousTime) << std::endl;
        previousTime = time;

        //camera
        {
            bool perspective = true;
            float translateZ = 0.f;
            float rotation = 0.f;
            bool enableDepth = true;
            // Set up projection
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity(); 
            if (perspective)
                gluPerspective(90, SCREEN_WIDTH / SCREEN_HEIGHT, 0.001, 60.f);
            else
               gluOrtho2D(-2.f, 2.f, 2.f / 90, 2.f / -90);

            // Set up model-view
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            if (perspective)
                glTranslatef(0.f, 0.f, translateZ);
            glScalef(0.6f, 0.6f, 0.6f);
            glRotatef(rotation, 0.f, 1.f, 0.f);

            // Enable/Disable capabilities
            glDisable(GL_TEXTURE_2D);
            glDisable(GL_BLEND);
            if (enableDepth)
                glEnable(GL_DEPTH_TEST);

            GLfloat fogColor[4] = {0.110*5, 0.177*5, 0.245*5, 1.0};
            glFogi(GL_FOG_MODE, GL_LINEAR);
            glFogfv(GL_FOG_COLOR, fogColor);
            glFogf(GL_FOG_DENSITY, 1.f);
            //glHint(GL_FOG_HINT, GL_DONT_CARE);
            glFogf(GL_FOG_START, 10.0);
            glFogf(GL_FOG_END, 20.0);
        }

        //glClearColor(0.5f, 0.5f, 0.5f, 1.f);
        glColor3f(0xFF, 0xFF, 0xFF);
        glClearColor(0.110*5, 0.177*5, 0.245*5, 0xFF);
        //updateColor(window);

        mainCamera.inputs(window);
        mainCamera.useTransform();
        glColor3f(1.f, 0.f, 0.f);
        tower.draw();

        glColor3f(0,0,1);
        moveCube(movingCube, time);
        glBegin(GL_QUADS);
        movingCube.draw();
        glEnd();

        inputs.put.onSwitch = [&]()
        {
            if (tower.addCubeOnTop(movingCube))
            {
                movingCube.minCoords.y += 0.1;
                movingCube.maxCoords.y += 0.1;  
                mainCamera.transform.location.y += 0.1;
            }
            else 
                std::cout << "lost" << std::endl;
        };
        inputs.put.input(glfwGetKey(window, GLFW_KEY_SPACE));

        glfwSwapBuffers(window);
    }

    glfwTerminate();

}