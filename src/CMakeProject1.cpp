// CMakeProject1.cpp : Defines the entry point for the application.

#include "CMakeProject1.h"

using namespace std;

const int WIDTH = 800, HEIGHT = 600;

float vertices[] = {
     // x,     y,    z
      0.f, 0.5f, 0.0f, 1.f, 0.f, 0.f, // top
     0.5f, -0.5f, 0.0f, 0.f, 1.f, 0.f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.f, 0.f, 1.f//, // bottom left

    //-.4f, .15f, 0.f, 0.f, 0.f, 1.f, // top
    //-.2f, -.2f, 0.f, 0.f, 0.f, 0.f, // right
    //-.6f, -.2f, 0.f, 1.f, 0.f, 0.f  // left
};
unsigned int indices[] = {
    0, 1, 2, // first Triangle
    //3, 4, 5 // second Triangle
};

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void process_input(GLFWwindow *window);

int main() 
{
  glfwInit();

  GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "title", NULL, NULL);
  glfwMakeContextCurrent(window);

  glfwWindowHint(GLFW_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_VERSION_MINOR, 3);


  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) 
  {
    cout << "failed to init glad\n";
  }

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  const char* vertShader = "vertexshader.vert";
  const char* fragShader = "fragmentshader.frag";

  Shaders shader(vertShader, fragShader);

  // -----------../resources/
  // VERTEX DATA
  // -----------
  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof (float), (void*) 0);
  glEnableVertexAttribArray (0);
  // color attribute
  glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof (float), (void*) (3 * sizeof (float)));
  glEnableVertexAttribArray (1);

  //glBindVertexArray(0); 

  // -------
  // PROGRAM
  // -------
  //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glfwSwapInterval(1);

  while (!glfwWindowShouldClose(window)) {
    process_input(window);

    glClearColor(.1f, .1f, .1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use();
    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);


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
