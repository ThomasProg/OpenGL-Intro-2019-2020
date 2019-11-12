#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <algorithm>
#include <queue>
#include <iostream>
#include "mesh.h"
#include "camera.h"

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

// S_Cube putBlockOnAnother(const S_Cube& cutCube, const S_Cube& stableCube)
// {
//   S_Cube newCube;

//   newCube.loc.x = std::max(cutCube.loc.x, stableCube.loc.x);
//   newCube.loc.y = std::max(cutCube.loc.y, stableCube.loc.y);

//   newCube.size.x = std::min(cutCube.size.x - (cutCube.loc.x - newCube.loc.x), stableCube.size.x);
//   newCube.size.y = std::min(cutCube.size.y - (cutCube.loc.y - newCube.loc.y), stableCube.size.y);

//   return newCube;
// }

int main(int ArgCount, char **Args)
{
  uint32_t windowFlags = SDL_WINDOW_OPENGL;
  SDL_Window* window = SDL_CreateWindow("OpenGL Test", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, windowFlags);
  if (window == NULL)
    return 0;

  SDL_GLContext context = SDL_GL_CreateContext(window);

  bool bRunning = true;
  int32_t FullScreen = 0;
  CubeTower tower;
  Camera mainCamera;

  while (bRunning)
  {
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

    mainCamera.useTransform();

    // glBegin(GL_LINES);
    // glColor3f(1.f, 0.f, 0.f);
    // glVertex3f(0.f, 0.f, 0.f);
    // glVertex3f(1.f, 0.f, 0.f);
    // glEnd();

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