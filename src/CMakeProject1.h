#pragma once

#include <iostream>
#include <string>

#include "shaders.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../thirdparty/stb_image.h"

using namespace std;

const int WIDTH = 800, HEIGHT = 600;

const char *vertexShader = "#version 330 core\n"
                           "layout(location = 0) in vec3 aPos;\n"
                           "layout(location = 1) in vec3 aCol;\n"
                           "layout(location = 2) in vec2 aTexCoord;\n"
                           "out vec3 ourColor;\n"
                           "out vec2 TexCoord;\n"
                           "void main() {\n"
                           "gl_Position = vec4(aPos, 1.0);\n"
                           "ourColor = aCol;\n"
                           "TexCoord = aTexCoord;\n"
                           "};\n";

const char *fragmentShader = "#version 330 core\n"
                             "out vec4 FragColor;\n"
                             "in vec3 ourColor;\n"
                             "in vec2 TexCoord;\n"
                             "uniform sampler2D ourTexture;\n"
                             "void main() {\n"
                             "FragColor = texture(ourTexture, TexCoord);\n"
                             "};\n";

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