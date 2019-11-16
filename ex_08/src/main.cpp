#include <cstdio>
#include <cmath>

#include "game.h"

#include "macros.h"
#include "tower.h"
#include "camera.h"
#include "doOnce.h"
#include "timeline.h"
#include "score.h"

void errorGLCallback(GLenum source, GLenum type, GLuint id, GLenum severity, 
                     GLsizei length, const GLchar *message, const void *userParam)
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
            mainCamera.transform.rotation.y 
                = interpolate(rotAnimation.startValue, rotAnimation.endValue, (currentTime - rotAnimation.startTime), 4);
                    
            deltaAddRot += mainCamera.transform.rotation.y;
        }
        else 
        {
            mainCamera.transform.rotation.y += deltaAddRot;
            if (mainCamera.transform.location.z * 10 < tower.getTowerSize())
            {
                mainCamera.transform.location.y -= 0.01;
                mainCamera.transform.location.z += 0.01;
            }
        }
    }
    else
    {
        if (currentTime - rotAnimation.startTime <= 1)
        {
             mainCamera.transform.location.y 
                 = interpolate(translateAnimation.startValue, translateAnimation.endValue, (currentTime - translateAnimation.startTime), 1);

            mainCamera.transform.rotation.y 
                = interpolate(rotAnimation.startValue, rotAnimation.endValue, (currentTime - rotAnimation.startTime));
        }
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
        glEnable(GL_LIGHT0); // specular
        glEnable(GL_LIGHT1);
        glEnable(GL_COLOR_MATERIAL);     

        //glEnable(GL_LIGHT1); //ambient light
        float ambient[4] = {1, 0, 0, 1};
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);

        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

        //materials
        GLfloat specular[4] = {0.9,0.9,0.9,1};
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        float shininess = 64;
        glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
        // GLfloat emission[4] = {0.3,0.3,0.3,1};
        // glMaterialfv(GL_FRONT, GL_EMISSION, emission);
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

void setupGLFor3D()
{
    bool perspective = true;
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
    if (bGameOver && inputs.put.isOn)
    {
        fadeReset.startTime  = currentTime;
        fadeReset.startValue = 0.f;
        fadeReset.endValue   = 1.f;
    }
    
    if (fadeReset.startValue != fadeReset.endValue && fadeReset.startTime + 3 < currentTime)
    {
        mainCamera.reset();
        mainCamera.transform.location.z = 2;
        mainCamera.transform.location.y += CUBE_HEIGHT;
        rotAnimation.reset();
        bGameOver = false;
        axisIsX = true;
        fadeReset.reset();
        //unsigned int nbCubes = tower.getTowerSize();
        tower.reset();

        //reset moving cube altitude
        movingCube = S_Cube(vector3D(-CUBE_HALF_SIZE, -CUBE_HALF_HEIGHT + CUBE_HEIGHT, -CUBE_HALF_SIZE), 
                            vector3D(CUBE_HALF_SIZE, CUBE_HALF_HEIGHT + CUBE_HEIGHT, CUBE_HALF_SIZE));
        //reset camera altitude
        //mainCamera.transform.location.y -= CUBE_HEIGHT * nbCubes;
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

void Game::render2D()
{
    glPopMatrix();
    setupGLForUI(SCREEN_WIDTH, SCREEN_HEIGHT);
    fade();

    score.setNumber(tower.getTowerSize());
    score.draw();

    glPopMatrix();
}

void Game::render3D()
{
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    tower.draw();

    animations();

    if (!bGameOver)
    {
        float rgb[3];
        std::tie(rgb[0], rgb[1], rgb[2]) = S_Cube::getColor(tower.getTowerSize());
        glColor3f(rgb[0], rgb[1], rgb[2]);
        movingCube.movingCubeTick(axisIsX, currentTime);
    }

    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT0);
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

                translateAnimation.startValue = mainCamera.transform.location.y;
                translateAnimation.endValue += CUBE_HEIGHT; //no bug when spamming
                translateAnimation.startTime = glfwGetTime();

                axisIsX = !axisIsX;

                //animation
                rotAnimation.startTime  = currentTime;
                rotAnimation.startValue = mainCamera.transform.rotation.y;
                rotAnimation.endValue  += 90.f;
            }
            else 
            {
                bGameOver = true;

                inputs.put.isOn = true; //to detect next space 
                //animation
                rotAnimation.startTime  = currentTime;
                rotAnimation.startValue = mainCamera.transform.rotation.y;
                rotAnimation.endValue  += 360.f;
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

        //std::cout << "FPS : " << 1 / mainCamera.deltaTime << std::endl;

        setupGLFor3D();
        glEnable(GL_DEPTH_TEST);
        glColor3f(0xFF, 0xFF, 0xFF);
        glClearColor(0.110*5, 0.177*5, 0.245*5, 0xFF);

        glPushMatrix();
        
        mainCamera.useTransform();
        
        //changing location, similar to the sun
        float loc2[4] = {1,2,3,1};
        loc2[1] = cos(currentTime);
        loc2[2] = sin(currentTime);
        glLightfv(GL_LIGHT0, GL_POSITION, loc2);
        //there are 2 lights for a better render
        float loc[4] = {-1,-2,-3,1};
        glLightfv(GL_LIGHT1, GL_POSITION, loc);


        render3D();

        inputs.test.input(glfwGetKey(window, GLFW_KEY_H));
        if (inputs.test.isOn)

        {
            for (unsigned int i = 0; i < 10; i++)
            {
                movingCube.minCoords.x = -500;
                movingCube.minCoords.z = -500;
                movingCube.maxCoords.x = 500;
                movingCube.maxCoords.z = 500;
                inputs.put.onSwitch();
                inputs.test.isOn = false;
            }
        }

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
