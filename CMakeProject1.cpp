// CMakeProject1.cpp : Defines the entry point for the application.

#include "CMakeProject1.h"

using namespace std;

const int WIDTH = 800, HEIGHT = 600;

float vertices[] = {
     // x,     y,    z
      0.f, 0.5f, 0.0f, 1.f, 0.f, 0.f, // top
     0.5f, -0.5f, 0.0f, 0.f, 1.f, 0.f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.f, 0.f, 1.f, // bottom left

    //-.4f, .15f, 0.f, 0.f, 0.f, 1.f, // top
    //-.2f, -.2f, 0.f, 0.f, 0.f, 0.f, // right
    //-.6f, -.2f, 0.f, 1.f, 0.f, 0.f  // left
};
unsigned int indices[] = {
    0, 1, 2, // first Triangle
    //3, 4, 5 // second Triangle
};

const char *vertexShaderSource =
  "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "layout (location = 1) in vec3 aCol;\n"
  "out vec3 vertexColor;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = vec4(aPos, 1.0);\n"
  "   vertexColor = aCol;\n"
  "}\0";

const char *fragmentShaderSource =
  "#version 330 core\n"
  "out vec4 FragColor;\n"
  "in vec3 vertexColor;\n"
  "void main()\n"
  "{\n"
  "   FragColor = vec4(vertexColor, 1.0f);\n"
  "}\0";

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


  int success;
  char infoLog[512];


  // -------------
  // VERTEX SHADER
  // -------------
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cerr << "VERTEX SHADER COMPILATION FAILED\n";
  }

  // ---------------
  // FRAGMENT SHADER
  // ---------------
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) 
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cerr << "FRAGMENT SHADER COMPILATION FAILED\n";
  }

  // --------------
  // SHADER PROGRAM
  // --------------
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if(!success)
  {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cerr << "SHADER PROGRAM LINK FAILED\n";
  }

  // -----------
  // VERTEX DATA
  // -----------
  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof (float), (void*) 0);
  glEnableVertexAttribArray (0);
  // color attribute
  glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof (float), (void*) (3 * sizeof (float)));
  glEnableVertexAttribArray (1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0); 

  // -------
  // PROGRAM
  // -------
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glfwSwapInterval(1);
  while (!glfwWindowShouldClose(window)) {
    process_input(window);

    glClearColor(.1f, .1f, .1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteProgram(shaderProgram);


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
