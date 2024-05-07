// CMakeProject1.cpp : Defines the entry point for the application.
//

#include "CMakeProject1.h"

using namespace std;

const int WIDTH = 800, HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void process_input(GLFWwindow *window);

int main() {
  glfwInit();

  GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "title", NULL, NULL);
  glfwMakeContextCurrent(window);

  glfwWindowHint(GLFW_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_VERSION_MINOR, 3);


  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    cout << "failed to init glad\n";
  }

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);




  glfwSwapInterval(1);
  while (!glfwWindowShouldClose(window)) {
    process_input(window);

    glClearColor(0.1f, 1.f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glad_glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
    glfwSetWindowShouldClose(window, true);
  }
}
