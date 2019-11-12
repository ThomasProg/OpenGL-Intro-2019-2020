#include <cstdio>

#include "macros.h"
#include "mesh.h"
#include "sphere.h"
#include "cone.h"
#include "cube.h"
#include "referential.h"
#include "doOnce.h"
#include "utilities.h"
#include "camera.h"
#include "maze.h"

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

void cameraCollisionWhileMoving(const Maze& maze, Camera& camera)
{
    Vector3 deltaLoc = camera.transform.location - camera.lastLocation;
    Vector3 testedLocation = camera.lastLocation;

    //We want the player to advance in every coordinates if possible.
    //Also, we want to stop the play going to this direction if there is a collision.
    //Hovever, we do not want the player to go into a block on a diagonale either.

    //the camera takes the hitbox of a box (cube).
    //constexpr float hitboxSize = 2.f; 

    testedLocation.x += camera.hitboxSize * deltaLoc.x;
    if (maze.isColliding(testedLocation))
    {
        camera.transform.location.x = camera.lastLocation.x;
        testedLocation.x = camera.lastLocation.x;
    }

    testedLocation.y += camera.hitboxSize * deltaLoc.y;
    if (maze.isColliding(testedLocation))
    {
        camera.transform.location.y = camera.lastLocation.y;
        testedLocation.y = camera.lastLocation.y;
    }

    testedLocation.z += camera.hitboxSize * deltaLoc.z;
    if (maze.isColliding(testedLocation))
    {
        camera.transform.location.z = camera.lastLocation.z;
        testedLocation.z = camera.lastLocation.z;
    }

    camera.lastLocation = camera.transform.location;
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

    //glScalef(600.f / float(SCREEN_HEIGHT), 600.f / float(SCREEN_WIDTH), 600.f / float(SCREEN_HEIGHT));

    S_Inputs inputs;
    //S_Path   path;

    Vector3 shapesLoc(0,0,0);
    //unsigned int currentIntersectIndex = 0;
    //float shapeLocRatio = 0.f;

    Camera mainCamera;
    Maze maze;

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

        cameraCollisionWhileMoving(maze, mainCamera);

        glLoadIdentity();
        mainCamera.useTransform();

        maze.render(mainCamera.transform.location);

        glfwSwapBuffers(window);
    }

    glfwTerminate();

}
