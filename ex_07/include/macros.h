#ifndef _MACROS_H_
#define _MACROS_H_

#include "glad/glad.h"
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>
#include <vector>

#define PI 3.14

constexpr int SCREEN_WIDTH  = 700;
constexpr int SCREEN_HEIGHT =  700;
constexpr float SPEED = 0.05f;
constexpr float SHAPE_SIZE = 200;

constexpr float SHAPE_SCREEN_SIZE_X = SHAPE_SIZE / SCREEN_WIDTH;
constexpr float SHAPE_SCREEN_SIZE_Y = SHAPE_SIZE / SCREEN_HEIGHT;
constexpr float SHAPE_SCREEN_SIZE_Z = SHAPE_SIZE / SCREEN_HEIGHT;

constexpr float BLOCK_SIZE  = 1;
constexpr int NB_ELEMENTS = 10;
constexpr float CHUNK_SIZE  = BLOCK_SIZE * NB_ELEMENTS;

#endif