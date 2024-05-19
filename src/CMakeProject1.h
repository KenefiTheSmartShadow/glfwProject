#pragma once

#include <iostream>
#include <string>

#include "shaders.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../thirdparty/stb_image.h"

using namespace std;

const int WIDTH = 800, HEIGHT = 600;

float vertices[] = {
    // positions          // colors         // texture coords
     0.5f,   0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
     0.5f,  -0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
    -0.5f,  -0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    -0.5f,   0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
};
unsigned int indices[] = {
    0, 1, 3, // first Triangle
    1, 2, 3  // second Triangle
};