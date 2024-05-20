#pragma once

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
// opengl math
#include <GLM/glm.hpp>

#include "../thirdparty/stb_image.h"


class camera
{
  glm::vec3 cameraPos = glm::vec3(0.f, 0.f, 3.f);
  glm::vec3 cameraTarget = glm::vec3(0.f, 0.f, 0.f);
  glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

  glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
  glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
  glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
};