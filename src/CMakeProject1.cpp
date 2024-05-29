#include "CMakeProject1.h"

// camera
Camera camera(glm::vec3(0.f, 0.f, 3.f));
float lastX = SCR_WIDTH / 2;
float lastY = SCR_HEIGHT / 2;
bool firstMouse = true;
bool useMouse = false;

// time
float deltaTime = 0.f;
float lastFrame = 0.f;

// cube
float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f,  0.0f,  0.5f,  -0.5f,
    -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f,  0.0f,  0.5f,  0.5f,  -0.5f, 0.0f,
    0.0f,  -1.0f, 1.0f,  1.0f,  0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f,
    1.0f,  1.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f,  0.0f,

    -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.5f,  -0.5f,
    0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,
    0.0f,  1.0f,  1.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    1.0f,  1.0f,  -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

    -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,
    -0.5f, -1.0f, 0.0f,  0.0f,  1.0f,  1.0f,  -0.5f, -0.5f, -0.5f, -1.0f,
    0.0f,  0.0f,  0.0f,  1.0f,  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,
    0.0f,  1.0f,  -0.5f, -0.5f, 0.5f,  -1.0f, 0.0f,  0.0f,  0.0f,  0.0f,
    -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f,  0.0f,

    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.5f,  0.5f,
    -0.5f, 1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.5f,  -0.5f, -0.5f, 1.0f,
    0.0f,  0.0f,  0.0f,  1.0f,  0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,
    0.0f,  1.0f,  0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f,  1.0f,  0.5f,  -0.5f,
    -0.5f, 0.0f,  -1.0f, 0.0f,  1.0f,  1.0f,  0.5f,  -0.5f, 0.5f,  0.0f,
    -1.0f, 0.0f,  1.0f,  0.0f,  0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,
    1.0f,  0.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f,  1.0f,

    -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.5f,  0.5f,
    -0.5f, 0.0f,  1.0f,  0.0f,  1.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0.0f,
    1.0f,  0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f,  1.0f};
// cube positions
glm::vec3 cubePositions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
    glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

// point light positions
glm::vec3 pointLightPositions[] = {
    glm::vec3(0.7f, 0.2f, 2.0f), glm::vec3(2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f, 2.0f, -12.0f), glm::vec3(0.0f, 0.0f, -3.0f)};

int main() {
  glfwInit();

  glfwWindowHint(GLFW_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_VERSION_MINOR, 3);

  // glfw window
  GLFWwindow *window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "title", NULL, NULL);
  glfwMakeContextCurrent(window);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    cout << "failed to init glad\n";
  }

  glEnable(GL_DEPTH_TEST);

  // imgui
  // -----
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  // styling
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init();
  // docking
  ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  // -------
  // SHADERS
  // -------
  Shaders cubeShader("resources/shaders/cubeVert.vert",
                     "resources/shaders/cubeFrag.frag");
  Shaders lightSource("resources/shaders/lightObjVert.vert",
                      "resources/shaders/lightObjFrag.frag");

  // -----------
  // VERTEX DATA
  // -----------

  // cube VAO
  // --------
  unsigned int VBO, cubeVAO;
  glGenVertexArrays(1, &cubeVAO);
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(cubeVAO);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // normal attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // texture attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  // TEXTURES
  // --------
  unsigned int diffuseMap = loadTexture("resources/images/container2.png");
  unsigned int specularMap =
      loadTexture("resources/images/container2_specular.png");
  // unsigned int emisiveMap = loadTexture("resources/images/matrix.jpg");

  cubeShader.use();
  cubeShader.setInt("material.diffuse", 0);
  cubeShader.setInt("material.specular", 1);
  // cubeShader.setInt("material.Emisive", 2);

  // emisive
  // glActiveTexture(GL_TEXTURE2);
  // glBindTexture(GL_TEXTURE_2D, emisiveMap);

  // light's VAO
  // -----------
  unsigned int lightCubeVAO;
  glGenVertexArrays(1, &lightCubeVAO);
  glBindVertexArray(lightCubeVAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // -------
  // PROGRAM
  // -------
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  while (!glfwWindowShouldClose(window)) {
    // per-frame time logic
    // --------------------
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // input
    // -----
    process_input(window);

    // render
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // be sure to activate shader when setting uniforms/drawing objects
    cubeShader.use();
    cubeShader.setVec3("viewPos", camera.Position);
    cubeShader.setFloat("material.shininess", 32.0f);

    // directional light
    cubeShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
    cubeShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    cubeShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    cubeShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
    // point light 1
    cubeShader.setVec3("pointLights[0].position", pointLightPositions[0]);
    cubeShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
    cubeShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
    cubeShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
    cubeShader.setFloat("pointLights[0].constant", 1.0f);
    cubeShader.setFloat("pointLights[0].linear", 0.09f);
    cubeShader.setFloat("pointLights[0].quadratic", 0.032f);
    // point light 2
    cubeShader.setVec3("pointLights[1].position", pointLightPositions[1]);
    cubeShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
    cubeShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
    cubeShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
    cubeShader.setFloat("pointLights[1].constant", 1.0f);
    cubeShader.setFloat("pointLights[1].linear", 0.09f);
    cubeShader.setFloat("pointLights[1].quadratic", 0.032f);
    // point light 3
    cubeShader.setVec3("pointLights[2].position", pointLightPositions[2]);
    cubeShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
    cubeShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
    cubeShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
    cubeShader.setFloat("pointLights[2].constant", 1.0f);
    cubeShader.setFloat("pointLights[2].linear", 0.09f);
    cubeShader.setFloat("pointLights[2].quadratic", 0.032f);
    // point light 4
    cubeShader.setVec3("pointLights[3].position", pointLightPositions[3]);
    cubeShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
    cubeShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
    cubeShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
    cubeShader.setFloat("pointLights[3].constant", 1.0f);
    cubeShader.setFloat("pointLights[3].linear", 0.09f);
    cubeShader.setFloat("pointLights[3].quadratic", 0.032f);
    // spotLight
    /*cubeShader.setVec3("spotLight.position", camera.Position);
    cubeShader.setVec3("spotLight.direction", camera.Front);
    cubeShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    cubeShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    cubeShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    cubeShader.setFloat("spotLight.constant", 1.0f);
    cubeShader.setFloat("spotLight.linear", 0.09f);
    cubeShader.setFloat("spotLight.quadratic", 0.032f);
    cubeShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    cubeShader.setFloat("spotLight.outerCutOff",
    glm::cos(glm::radians(15.0f)));*/

    // view/projection transformations
    glm::mat4 projection =
        glm::perspective(glm::radians(camera.Zoom),
                         (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    cubeShader.setMat4("projection", projection);
    cubeShader.setMat4("view", view);

    // world transformation
    glm::mat4 model = glm::mat4(1.0f);
    cubeShader.setMat4("model", model);

    // bind diffuse map
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseMap);
    // bind specular map
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularMap);

    // render containers
    glBindVertexArray(cubeVAO);
    for (unsigned int i = 0; i < 10; i++) {
      // calculate the model matrix for each object and pass it to shader before
      // drawing
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);
      float angle = 20.0f * i;
      model =
          glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
      cubeShader.setMat4("model", model);

      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // also draw the lamp object(s)
    lightSource.use();
    lightSource.setMat4("projection", projection);
    lightSource.setMat4("view", view);
    lightSource.setVec3("lightCol", glm::vec3(1.0));

    // we now draw as many light bulbs as we have point lights.
    glBindVertexArray(lightCubeVAO);
    for (unsigned int i = 0; i < 4; i++) {
      model = glm::mat4(1.0f);
      model = glm::translate(model, pointLightPositions[i]);
      model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
      lightSource.setMat4("model", model);
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();

    // toggle mouse input
    if (!useMouse)
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    else
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &cubeVAO);
  glDeleteVertexArrays(1, &lightCubeVAO);
  glDeleteBuffers(1, &VBO);
  // glDeleteBuffers(1, &EBO);

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();
}

void process_input(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  // camera movement
  if (useMouse) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
      camera.ProcessKeyboard(DOWN, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
      camera.ProcessKeyboard(UP, deltaTime);
  }
}

void framebuffer_size_callback(GLFWwindow *window, int SRC_WIDTH,
                               int SRC_HEIGHT) {
  glad_glViewport(0, 0, SRC_WIDTH, SRC_HEIGHT);
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {
  float xpos = static_cast<float>(xposIn);
  float ypos = static_cast<float>(yposIn);

  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset =
      lastY - ypos; // reversed since y-coordinates go from bottom to top

  lastX = xpos;
  lastY = ypos;

  if (useMouse)
    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
  camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void mouse_button_callback(GLFWwindow *window, int button, int action,
                           int mods) {
  if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    useMouse = true;
  if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    useMouse = false;
}

unsigned int loadTexture(const char *path) {
  unsigned int textureID;
  glGenTextures(1, &textureID);

  int SRC_WIDTH, SRC_HEIGHT, nrComponents;
  unsigned char *data =
      stbi_load(path, &SRC_WIDTH, &SRC_HEIGHT, &nrComponents, 0);
  if (data) {
    GLenum format;
    if (nrComponents == 1)
      format = GL_RED;
    else if (nrComponents == 3)
      format = GL_RGB;
    else if (nrComponents == 4)
      format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, SRC_WIDTH, SRC_HEIGHT, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
  } else {
    cerr << "Failed to load texture " << path << "\n";
    stbi_image_free(data);
  }

  return textureID;
}

void runGUI() {
  // imgui input values

  ImGui::Begin("Debug");

  ImGui::End();

  ImGui::Render();
}