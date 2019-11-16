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

constexpr float CUBE_SIZE   = 0.5f;
constexpr float CUBE_HEIGHT = 0.1f;

constexpr float CUBE_HALF_SIZE = CUBE_SIZE / 2;
constexpr float CUBE_HALF_HEIGHT    = CUBE_HEIGHT / 2;

constexpr float moveDistance = 1; 
constexpr float moveSpeed    = 1;

#define TOWER_MAX_SIZE 5000

#endif