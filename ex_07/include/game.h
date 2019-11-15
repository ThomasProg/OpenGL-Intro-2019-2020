#ifndef _GAME_H_
#define _GAME_H_

#include "doOnce.h"

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

#include "maze.h"
#include "camera.h"
#include "lightManager.h"

#include "macros.h"

class Game
{
private:
    S_Inputs inputs;

    Camera mainCamera;
    Maze maze;

    GLFWwindow* window;
    LightManager lightning;

    Game() = delete; //delete default constructor
public:
    Game(bool& isValid);
    ~Game();
    void render();
    void collision();
    void loop();


    int w;
    int h;
    int comp;
    std::string filename = "media/stone.png";
    unsigned char* image;
    GLuint texture;
};

#endif