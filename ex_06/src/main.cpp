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

void moveShape(GLFWwindow* window, S_Inputs& inputs, Mesh& mesh)
{
    inputs.x.input(glfwGetKey(window, GLFW_KEY_X));
    if (inputs.x.isOn)
    {
        //glRotated(rotationSpeed, 1.f, 0.f, 0.f);
        mesh.transform.rotation.x+=1.f;
    }

    inputs.y.input(glfwGetKey(window, GLFW_KEY_Y));
    if (inputs.y.isOn)
    {
        //glRotated(rotationSpeed, 0.f, 1.f, 0.f);
        mesh.transform.rotation.y += 1.f;
    }
    
    inputs.z.input(glfwGetKey(window, GLFW_KEY_Z));
    if (inputs.z.isOn)
    {
        //glRotated(rotationSpeed, 0.f, 0.f, 1.f);
        mesh.transform.rotation.z += 1.f;
    }
    
    if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) || glfwGetKey(window, GLFW_KEY_MINUS))
    {
        //glScalef(1.f - scaleSpeed, 1.f - scaleSpeed, 1.f - scaleSpeed);
        mesh.transform.scale.x *= 1.f - scaleSpeed;
        mesh.transform.scale.y *= 1.f - scaleSpeed;
        mesh.transform.scale.z *= 1.f - scaleSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_KP_ADD)  || glfwGetKey(window, GLFW_KEY_EQUAL))
    {
        //glScalef(1.f + scaleSpeed, 1.f + scaleSpeed, 1.f + scaleSpeed);
        mesh.transform.scale.x *= 1.f + scaleSpeed;
        mesh.transform.scale.y *= 1.f + scaleSpeed;
        mesh.transform.scale.z *= 1.f + scaleSpeed;
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
        mesh.setMesh(E_MeshType::E_SPHERE);
        //    mesh.bIsSphere = true;
        //}
        mesh.draw();
    }

    if (glfwGetKey(window, GLFW_KEY_2))
    {
        mesh.setMesh(E_MeshType::E_CUBE);
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

// struct S_Path
// {
//     std::vector<vec2> points;
//     bool bIsOpen = false;

//     void addPoint(GLFWwindow* window)
//     {
//         if (bIsOpen)
//         {
//             bIsOpen = false;
//             points.clear();
//         }

//         double x, y;
//         glfwGetCursorPos(window, &x, &y);

//         x -= double(SCREEN_WIDTH)/2.0;
//         y -= double(SCREEN_HEIGHT)/2.0;

//         x /= double(SCREEN_WIDTH);
//         y /= double(SCREEN_HEIGHT);

//         x *= 2;
//         y *= 2;

//         // x -= 0.5f;
//         // y -= 0.5f;
//         // x -= 1.f;
//         // y -= 1.f;
//         y *= -1.f;

//         points.push_back(vec2(x, y));
//     }
// };

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

    glEnable(GL_DEPTH_TEST);

    //glScalef(600.f / float(SCREEN_HEIGHT), 600.f / float(SCREEN_WIDTH), 600.f / float(SCREEN_HEIGHT));

    S_Inputs inputs;
    //S_Path   path;

    Vector3 shapesLoc(0,0,0);
    //unsigned int currentIntersectIndex = 0;
    //float shapeLocRatio = 0.f;

    Mesh mesh;
    Mesh playerMesh;
    Camera mainCamera;
    Maze maze;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //glOrtho(-5, 5, -5, 5, -50, 50);
    //glLoadIdentity();

    double previousTime = glfwGetTime();
    glEnable(GL_FOG);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double time =  glfwGetTime();
        mainCamera.deltaTime = time - previousTime;
        std::cout << "FPS : " << 1/(time - previousTime) << std::endl;
        previousTime = time;

        //std::cout << "Player Loc : " << mainCamera.transform.location.x << std::endl;

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

        glPushMatrix();
        playerMesh.setMesh(E_MeshType::E_CUBE);
        // glLoadIdentity();
        // glTranslatef(0,0,1);
        // playerMesh.useTransform();
        playerMesh.draw();
        glPopMatrix();
        //mesh.transform.location.x -= 0.003;

        maze.render(mainCamera.transform.location);

        glPushMatrix();
        //mesh.setMesh(E_MeshType::E_CUBE);
        mesh.setMesh(E_MeshType::E_MAZE);
        glTranslatef(0, -1.9, 0);
        drawRef();
        glScalef(5,0.5,5);
        mesh.useTransform();
        mesh.draw();
        glPopMatrix();

        // inputs.showEdges.input(glfwGetKey(window, GLFW_KEY_M));
        // //mesh.drawMode = inputs.showEdges.isOn ? GL_LINE_LOOP : GL_TRIANGLE_FAN;
        // mesh.bShowEdges = inputs.showEdges.isOn;

        // inputs.leftMouseClick.input(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT));

        // inputs.rightMouseClick.input(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT));

        // inputs.leftMouseClick.onSwitch = [&]()
        // {
        //         path.addPoint(window);
        // };
        // inputs.rightMouseClick.onSwitch = [&]()
        // {
        //         path.addPoint(window);
        //         path.bIsOpen = true;
        // };

        //drawRef();

        // if (path.bIsOpen)
        // {
        //     glPushMatrix();
        //     glScalef(float(SCREEN_HEIGHT) / 600.f, float(SCREEN_WIDTH) / 600.f, float(SCREEN_HEIGHT) / 600.f);

        //     glBegin(GL_LINE_LOOP);
        //     for (unsigned int i = 0; i < path.points.size(); i++)
        //     {
        //         float ratio = float(i) / float(path.points.size());
        //         {
        //             glColor4f(1.f - ratio, 0.f, ratio, ratio);
        //             float x = path.points[i].x;
        //             float y = path.points[i].y;
        //             glVertex3f(x, y, 0);
        //         }
        //     }
        //     glEnd();
        //     glPopMatrix();
        // }

        // {
        //     if (path.points.size() != 0 && path.bIsOpen)
        //     {
        //         glPushMatrix();

        //         vec2 translation(0,0);
        //         translation.x = shapesLoc.x - path.points[(currentIntersectIndex + 1) % path.points.size()].x;
        //         translation.y = shapesLoc.y - path.points[(currentIntersectIndex + 1) % path.points.size()].y;

        //         unsigned int i = currentIntersectIndex;
        //         while (vec2(translation.x, translation.y).length() < 0.03 && (currentIntersectIndex + 1) % path.points.size() != i)
        //         {
        //             currentIntersectIndex++;
        //             currentIntersectIndex%= path.points.size();
        //             translation.x = shapesLoc.x - path.points[(currentIntersectIndex + 1) % path.points.size()].x;
        //             translation.y = shapesLoc.y - path.points[(currentIntersectIndex + 1) % path.points.size()].y;
        //         }
        //         translation = translation.unit();
        //         translation.x *= -0.01;
        //         translation.y *= -0.01;
        //         glTranslatef(shapesLoc.x + translation.x, shapesLoc.y + translation.y, 0);
        //         shapesLoc.x += translation.x;
        //         shapesLoc.y += translation.y;

        //         glScalef(0.1, 0.1, 0.1);
        //         moveShape(window, inputs, mesh);
        //         mesh.useTransform();
        //         // glTranslatef(mesh.location.x, mesh.location.y, mesh.location.z);
        //         // glScalef(mesh.scale.x, mesh.scale.y, mesh.scale.z);
        //         // glRotated(mesh.rotation.x, 1, 0, 0);
        //         // glRotated(mesh.rotation.y, 0, 1, 0);
        //         // glRotated(mesh.rotation.z, 0, 0, 1);

        //         drawShapes(window, mesh, inputs.showEdges.isOn);
        //         if (glfwGetKey(window, GLFW_KEY_3))
        //             drawRef();

        //         glPopMatrix();
        //     }
        // }

        glfwSwapBuffers(window);
    }

    glfwTerminate();

}