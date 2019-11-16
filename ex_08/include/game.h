#ifndef _GAME_H_
#define _GAME_H_

#include "macros.h"
#include "tower.h"
#include "camera.h"
#include "doOnce.h"
#include "timeline.h"

#include "score.h"

struct S_Inputs
{
    S_DoOnce put;
    S_DoOnce test;
};

class Game
{
    GLFWwindow* window;
    Camera mainCamera;

    CubeTower tower;
    S_Cube movingCube = S_Cube(vector3D(-CUBE_HALF_SIZE, -CUBE_HALF_HEIGHT + CUBE_HEIGHT, -CUBE_HALF_SIZE), 
                      vector3D(CUBE_HALF_SIZE, CUBE_HALF_HEIGHT + CUBE_HEIGHT, CUBE_HALF_SIZE));
    bool bGameOver = false;

public:
    TimeLine rotAnimation;
    TimeLine translateAnimation;
    TimeLine fadeReset;

    Score score;
    S_Inputs inputs;
    bool axisIsX = true;
    float deltaAddRot = 0.f;

    float currentTime = 0.f;

    Game() 
    {
        mainCamera.transform.location.z = 2;
        mainCamera.transform.location.y += CUBE_HEIGHT;
    }

    ~Game() {}

    void animations();
    int start();
    void fade();

    void render2D();
    void render3D();
};

#endif