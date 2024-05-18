#include "CMakeProject1.h"

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

  Shaders shader(vertexShader, fragmentShader);

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
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof (float), (void*) 0);
  glEnableVertexAttribArray (0);
  // color attribute
  glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof (float), (void*) (3 * sizeof (float)));
  glEnableVertexAttribArray (1);
  // texture coords attribute
  glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof (float), (void*) (6 * sizeof(float)));
  glEnableVertexAttribArray (2);

  //glBindVertexArray(0); 

  // --------
  // TEXTURES
  // --------
  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  // texture wrapping
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // texture filtering
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
  // load texture
  int width, height, nrChannels;
  // TODO: get image to load correctly
  unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

  if (data) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                   GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    cerr << "ERROR: FAILED TO LOAD TEXTURE\n";
  }

  stbi_image_free(data);

  // -------
  // PROGRAM
  // -------
  //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glfwSwapInterval(1);

  while (!glfwWindowShouldClose(window)) {
    process_input(window);

    glClearColor(.1f, .1f, .1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, texture);

    shader.use();
    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);


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
