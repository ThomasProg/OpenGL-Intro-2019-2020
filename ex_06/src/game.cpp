#include "game.h"

#include "macros.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

constexpr float rotationSpeed = 0.5f;
constexpr float scaleSpeed = 1.f / 10.f;

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

void setFog()
{
    GLfloat fogColor[4] = {0.110*5, 0.177*5, 0.245*5, 1.0};
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_DENSITY, 1.f);
    glFogf(GL_FOG_START, 10.0);
    glFogf(GL_FOG_END, 100.0);
}

Game::Game(bool& isValid)
{
    if (!glfwInit())
    {
        isValid = false;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Geometry", NULL, NULL);

    glfwMakeContextCurrent(window);

    if (!gladLoadGL())
    {
        glfwTerminate();
        isValid = false;
        return;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_FOG);
    setFog();

    //load texture
    {
        image = stbi_load(filename.c_str(), &w, &h, &comp, STBI_rgb);

        //glEnable(GL_TEXTURE_2D);

        glGenTextures(1, &texture);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        //there's only one texture
    }

    isValid = true;
    return;
}

void Game::render()
{
    glEnable(GL_TEXTURE_2D);

    maze.render(mainCamera.transform.location);

    glDisable(GL_TEXTURE_2D);
}

void Game::collision()
{

}

void Game::loop()
{
    double previousTime = glfwGetTime();

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
            glDisable(GL_BLEND);
            if (enableDepth)
                glEnable(GL_DEPTH_TEST);
        }

        glClearColor(0.110*5, 0.177*5, 0.245*5, 0xFF);

        mainCamera.inputs(window);

        cameraCollisionWhileMoving(maze, mainCamera);

        glLoadIdentity();
        mainCamera.useTransform();

        render();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
}