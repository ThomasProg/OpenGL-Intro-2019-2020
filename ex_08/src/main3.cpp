#include <cstdio>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "transform.h"
#include "camera.h"
#include "macros.h"
#include "mesh.h"
//#include "camera.h"

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

constexpr float rotationSpeed = 0.5f;
constexpr float scaleSpeed = 1.f / 10.f;

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
    if (perspective)
        glTranslatef(0.f, 0.f, translateZ);
    glScalef(0.6f, 0.6f, 0.6f);
    glRotatef(rotation, 0.f, 1.f, 0.f);

    // Enable/Disable capabilities
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    if (enableDepth)
        glEnable(GL_DEPTH_TEST);

    //fog
    GLfloat fogColor[4] = {0.110*5, 0.177*5, 0.245*5, 1.0};
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_DENSITY, 1.f);
    //glHint(GL_FOG_HINT, GL_DONT_CARE);
    glFogf(GL_FOG_START, 10.0);
    glFogf(GL_FOG_END, 20.0);
}

int main(int ArgCount, char **Args)
{
    uint32_t windowFlags = SDL_WINDOW_OPENGL;
    SDL_Window* window = SDL_CreateWindow("OpenGL Test", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, windowFlags);
    if (window == NULL)
      return 0;

    SDL_GLContext context = SDL_GL_CreateContext(window);

    glEnable(GL_DEPTH_TEST);

    Vector3 shapesLoc(0,0,0);

    Camera mainCamera;

    glEnable(GL_FOG);

    bool bRunning = true;
    int32_t FullScreen = 0;
    CubeTower tower;

    while (bRunning)
    {
      openGLSet();
      mainCamera.useTransform();

      //glClearColor(0.5f, 0.5f, 0.5f, 1.f);
      glColor3f(0xFF, 0xFF, 0xFF);
      glClearColor(0.110*5, 0.177*5, 0.245*5, 0xFF);

      //gluLookAt(1, 1, 1, 0, 0, 0, 1, 1, 1);
      tower.draw();
      SDL_Event event;
      while (SDL_PollEvent(&event))
      {
          mainCamera.inputs(event);
          if (event.type == SDL_KEYDOWN)
          {
              switch (event.key.keysym.sym)
              {
                case SDLK_ESCAPE:
                  bRunning = false;
                  break;
                case 'f':
                  FullScreen = !FullScreen;
                  if (FullScreen)
                  {
                    SDL_SetWindowFullscreen(window, windowFlags | SDL_WINDOW_FULLSCREEN_DESKTOP);
                  }
                  else
                  {
                    SDL_SetWindowFullscreen(window, windowFlags);
                  }
                  break;
                default:
                  break;
              }
          }
          else if (event.type == SDL_QUIT)
          {
            bRunning = 0;
          }
      }

      SDL_GL_SwapWindow(window); //display opengl drawings
      glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
      glClearColor(1.f, 1.f, 1.f, 0.f);
      glClear(GL_COLOR_BUFFER_BIT);
    }

  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}


// int main()
// {
//     if (!glfwInit())
//     {
//         return -1;
//     }

//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);


//     GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Geometry", NULL, NULL);

//     glfwMakeContextCurrent(window);

//     if (!gladLoadGL())
//     {
//         glfwTerminate();
//         return -1;
//     }

//     glEnable(GL_DEPTH_TEST);

//     //glScalef(600.f / float(SCREEN_HEIGHT), 600.f / float(SCREEN_WIDTH), 600.f / float(SCREEN_HEIGHT));

//     Vector3 shapesLoc(0,0,0);
//     //unsigned int currentIntersectIndex = 0;
//     //float shapeLocRatio = 0.f;

//     Camera mainCamera;

//     glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

//     double previousTime = glfwGetTime();
//     glEnable(GL_FOG);

//     while (!glfwWindowShouldClose(window))
//     {
//         glfwPollEvents();

//         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//         double time =  glfwGetTime();
//         mainCamera.deltaTime = time - previousTime;
//         //FPS
//         //std::cout << "FPS : " << 1/(time - previousTime) << std::endl;
//         previousTime = time;

//         //camera
//         {
//             bool perspective = true;
//             float translateZ = 0.f;
//             float rotation = 0.f;
//             bool enableDepth = true;
//             // Set up projection
//             glMatrixMode(GL_PROJECTION);
//             glLoadIdentity(); 
//             if (perspective)
//                 gluPerspective(90, SCREEN_WIDTH / SCREEN_HEIGHT, 0.001, 60.f);
//             else
//                gluOrtho2D(-2.f, 2.f, 2.f / 90, 2.f / -90);

//             // Set up model-view
//             glMatrixMode(GL_MODELVIEW);
//             glLoadIdentity();
//             if (perspective)
//                 glTranslatef(0.f, 0.f, translateZ);
//             glScalef(0.6f, 0.6f, 0.6f);
//             glRotatef(rotation, 0.f, 1.f, 0.f);

//             // Enable/Disable capabilities
//             glDisable(GL_TEXTURE_2D);
//             glDisable(GL_BLEND);
//             if (enableDepth)
//                 glEnable(GL_DEPTH_TEST);

//             GLfloat fogColor[4] = {0.110*5, 0.177*5, 0.245*5, 1.0};
//             glFogi(GL_FOG_MODE, GL_LINEAR);
//             glFogfv(GL_FOG_COLOR, fogColor);
//             glFogf(GL_FOG_DENSITY, 1.f);
//             //glHint(GL_FOG_HINT, GL_DONT_CARE);
//             glFogf(GL_FOG_START, 10.0);
//             glFogf(GL_FOG_END, 20.0);
//         }

//         //glClearColor(0.5f, 0.5f, 0.5f, 1.f);
//         glColor3f(0xFF, 0xFF, 0xFF);
//         glClearColor(0.110*5, 0.177*5, 0.245*5, 0xFF);
//         //updateColor(window);

//         mainCamera.inputs(window);

//         glLoadIdentity();
//         mainCamera.useTransform();

//         glfwSwapBuffers(window);
//     }

//     glfwTerminate();

// }