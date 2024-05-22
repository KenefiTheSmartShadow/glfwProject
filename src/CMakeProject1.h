#pragma once

#include <iostream>
#include <string>

#include "shaders.h"
#include "camera.h"

// imGui
#include <ImGui-Docking/ImGUI/imgui.h>
#include <ImGui-Docking/ImGUI/backends/imgui_impl_glfw.h>
#include <ImGui-Docking/ImGUI/backends/imgui_impl_opengl3.h>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
// opengl math
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "../thirdparty/stb_image.h"

using namespace std;

const int WIDTH = 1800, HEIGHT = 1200;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xposIN, double yposIN);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void process_input(GLFWwindow *window);

void runGUI();

// https://learnopengl.com/Lighting/Basic-Lighting