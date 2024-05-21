#pragma once

#include <iostream>
#include <string>

#include "shaders.h"
#include "camera.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
// opengl math
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "../thirdparty/stb_image.h"

using namespace std;

const int WIDTH = 800, HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xposIN, double yposIN);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void process_input(GLFWwindow *window);

Camera camera(glm::vec3(0.f, 0.f, 3.f));
float lastX = WIDTH  / 2;
float lastY = HEIGHT / 2;
bool firstMouse = true;

// time
float deltaTime = 0.f;
float lastFrame = 0.f;

// lighting
glm::vec3 lightPos(1.2f, 1.f, 2.f);
glm::vec3 lightColor(1.f, 1.f, 1.f);
glm::vec3 toyColor(1.f, .5f, .31f);
glm::vec3 result = lightColor * toyColor;

float vertices[] = {
    -0.5f, -0.5f, -0.5f,
    0.5f,  -0.5f, -0.5f,
    0.5f,  0.5f,  -0.5f,
    0.5f,  0.5f,  -0.5f,
    -0.5f, 0.5f,  -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f, 0.5f,
    0.5f,  -0.5f, 0.5f,
    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    -0.5f, 0.5f,  0.5f,
    -0.5f, -0.5f, 0.5f,

    -0.5f, 0.5f,  0.5f,
    -0.5f, 0.5f,  -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, 0.5f,
    -0.5f, 0.5f,  0.5f,

    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  -0.5f,
    0.5f,  -0.5f, -0.5f,
    0.5f,  -0.5f, -0.5f,
    0.5f,  -0.5f, 0.5f,
    0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
    0.5f,  -0.5f, -0.5f,
    0.5f,  -0.5f, 0.5f,
    0.5f,  -0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, 0.5f,  -0.5f,
    0.5f,  0.5f,  -0.5f,
    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    -0.5f, 0.5f,  0.5f,
    -0.5f, 0.5f,  -0.5f
};

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),    
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f), 
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),   
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

// https://learnopengl.com/Lighting/Colors