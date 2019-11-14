#include <cstdio>
#include <cmath>

#include "game.h"

#include "macros.h"
#include "mesh.h"
#include "camera.h"
#include "movingCube.h"
#include "doOnce.h"
#include "timeline.h"
#include "score.h"
#include "referential.h"

constexpr float rotationSpeed = 0.5f;
constexpr float scaleSpeed = 1.f / 10.f;

void input()
{

}

void errorGLCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
    fprintf(stderr, "GL error: %s (code=%d)\n", message, id);
}

void Game::animations()
{
    if (bGameOver)
    {
        if ((currentTime - rotAnimation.startTime) <= 2)
        {
            deltaAddRot = - mainCamera.transform.rotation.y;
            mainCamera.transform.rotation.y = interpolate(rotAnimation.startValue, rotAnimation.endValue, (currentTime - rotAnimation.startTime), 4);
            deltaAddRot += mainCamera.transform.rotation.y;
        }
        else 
        {
            mainCamera.transform.rotation.y += deltaAddRot;
            //mainCamera.down(1);
            // mainCamera.transform.location.x -= 0.01;
            // mainCamera.transform.location.y -= 0.01;
            // mainCamera.transform.location.z -= 0.01;
        }
    }
    else
    {
        if (currentTime - rotAnimation.startTime <= 1)
            mainCamera.transform.rotation.y = interpolate(rotAnimation.startValue, rotAnimation.endValue, (currentTime - rotAnimation.startTime));
    }
}

GLFWwindow* openGLInit()
{
    if (!glfwInit())
    {
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_SAMPLES, 4);
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Geometry", NULL, NULL);

    glfwMakeContextCurrent(window);

    if (!gladLoadGL())
    {
        glfwTerminate();
        return nullptr;
    }

    glDebugMessageCallback(errorGLCallback, nullptr);
    glEnable(GL_BLEND);
    glEnable(GL_MULTISAMPLE);  

    //light
    {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_COLOR_MATERIAL);     
    }
    
    return window;
}

void setupGLForUI(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, (GLdouble)SCREEN_WIDTH, SCREEN_HEIGHT, (GLdouble)0, -1, 10);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
}

void openGLSet()
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

    // Enable/Disable capabilities
    glDisable(GL_TEXTURE_2D);

    //fog
    GLfloat fogColor[4] = {0.110*5, 0.177*5, 0.245*5, 1.0};
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_DENSITY, 1.f);
    //glHint(GL_FOG_HINT, GL_DONT_CARE);
    glFogf(GL_FOG_START, 10.0);
    glFogf(GL_FOG_END, 20.0);
}

void Game::fade()
{
    //fade
    {
        if (bGameOver && inputs.put.isOn)
        {
            fadeReset.startTime  = currentTime;
            fadeReset.startValue = 0.f;
            fadeReset.endValue   = 1.f;
        }
        
        if (fadeReset.startValue != fadeReset.endValue && fadeReset.startTime + 3 < currentTime)
        {
            //camera.reset()
            mainCamera.transform.rotation.y = 0;
            rotAnimation.reset();
            bGameOver = false;
            axisIsX = true;
            fadeReset.reset();
            unsigned int nbCubes = tower.getTowerSize();
            tower.reset();

            //reset moving cube altitude
            movingCube = S_Cube(vector3D(-CUBE_HALF_SIZE, -CUBE_HALF_HEIGHT + CUBE_HEIGHT, -CUBE_HALF_SIZE), 
                                vector3D(CUBE_HALF_SIZE, CUBE_HALF_HEIGHT + CUBE_HEIGHT, CUBE_HALF_SIZE));
            //reset camera altitude
            mainCamera.transform.location.y -= CUBE_HEIGHT * nbCubes;
        }
            

        float fadeValue = fadeReset.interp(currentTime, 3);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0,0,0,fadeValue);
        glBegin(GL_QUADS);
        glVertex3f(-1, -1, 0);
        glVertex3f(-1, 1, 0);
        glVertex3f(1, 1, 0);
        glVertex3f(1, -1, 0);
        glEnd();
    }
}

void Game::render2D()
{
    //glDisable(GL_LIGHT0);
    glPopMatrix();
    setupGLForUI(SCREEN_WIDTH, SCREEN_HEIGHT);
    fade();

    score.setNumber(tower.getTowerSize());
    score.draw();

    glPopMatrix();
    //glEnable(GL_LIGHT0);
}

void Game::render3D()
{

}

int Game::start()
{
    window = openGLInit();
    if (window == nullptr)
        return EXIT_FAILURE;

    inputs.put.onSwitch = [this]()
    {
        if (!bGameOver)
        {
            if (tower.addCubeOnTop(movingCube))
            {
                movingCube.minCoords.y += CUBE_HEIGHT;
                movingCube.maxCoords.y += CUBE_HEIGHT;  
                mainCamera.transform.location.y += CUBE_HEIGHT;
                axisIsX = !axisIsX;

                //animation
                rotAnimation.startTime = currentTime;
                rotAnimation.startValue = mainCamera.transform.rotation.y;
                rotAnimation.endValue += 90.f;
            }
            else 
            {
                bGameOver = true;

                inputs.put.isOn = true; //to detect next space 
                //animation
                rotAnimation.startTime = currentTime;
                rotAnimation.startValue = mainCamera.transform.rotation.y;
                rotAnimation.endValue += 360.f;
            }
        }
    };

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    double previousTime = glfwGetTime();
    glEnable(GL_FOG);
    //setupGLForDrawing(SCREEN_WIDTH, SCREEN_HEIGHT);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        currentTime =  glfwGetTime();
        mainCamera.deltaTime = currentTime - previousTime;
        previousTime = currentTime;

        //setupGLForDrawing(SCREEN_WIDTH, SCREEN_HEIGHT);
        openGLSet();
        glEnable(GL_DEPTH_TEST);
        glColor3f(0xFF, 0xFF, 0xFF);
        glClearColor(0.110*5, 0.177*5, 0.245*5, 0xFF);

        float loc[4] = {1,1,1,0};
        glLightfv(GL_LIGHT0, GL_POSITION, loc);
        glPushMatrix();
        mainCamera.useTransform();

        // glPushMatrix();
        // drawRef();
        // glPopMatrix(); 
        // glColor3f(1.f, 0.f, 0.f);

        tower.draw();

        animations();

        if (!bGameOver)
            movingCube.movingCubeTick(axisIsX, currentTime);

        inputs.put.input(glfwGetKey(window, GLFW_KEY_SPACE));
        mainCamera.inputs(window);
        render2D();
        glPopMatrix();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

int main()
{
    Game game;
    return game.start();
}
