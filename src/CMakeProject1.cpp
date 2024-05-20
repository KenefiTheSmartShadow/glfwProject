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

  Shaders shader("resources/shaders/vertex.vert", "resources/shaders/fragment.frag");

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
  glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof (float), (void*) 0);
  glEnableVertexAttribArray (0);
  //// color attribute
  //glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof (float), (void*) (3 * sizeof (float)));
  //glEnableVertexAttribArray (1);
  // texture coords attribute
  glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof (float), (void*) (3 * sizeof(float)));
  glEnableVertexAttribArray (1);

  //glBindVertexArray(0); 

  // --------
  // TEXTURES
  // --------
  unsigned int texture1, texture2;
  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);
  // texture wrapping
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // texture filtering
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
  // load texture
  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  
  unsigned char *data = stbi_load("resources/images/container.jpg", &width, &height, &nrChannels, 0);

  if (data) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                   GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    cerr << "ERROR: FAILED TO LOAD TEXTURE\n";
  }

  stbi_image_free(data);

  glGenTextures(1, &texture2);
  glBindTexture(GL_TEXTURE_2D, texture2);
  // texture wrapping
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // texture filtering
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // load texture
  data = stbi_load("resources/images/awesomeface.png", &width, &height, &nrChannels, 0);

  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    cerr << "ERROR: FAILED TO LOAD TEXTURE\n";
  }

  stbi_image_free(data);

  shader.use();
  shader.setInt("texture1", 0);
  shader.setInt("texture2", 1);

  // -------
  // PROGRAM
  // -------
  //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glfwSwapInterval(1);

  glEnable(GL_DEPTH_TEST);

  while (!glfwWindowShouldClose(window)) {
    // window input
    process_input(window);
    
    // render
    glClearColor(.1f, .1f, .1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // textures
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    shader.use();

    // create transformations
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 view       = glm::mat4(1.0f);

    projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    view       = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    shader.setMat4("projection", projection);
    shader.setMat4("view", view);

    glBindVertexArray(VAO);
    for (unsigned int i = 0; i < 10; i++) {
      glm::mat4 model = glm::mat4(1.f);
      model = glm::translate(model, cubePositions[i]);
      float angle = 20.f * i;
      model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.f, .3f, .5f));
      shader.setMat4("model", model);

      glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}
