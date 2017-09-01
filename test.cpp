// Include standard headers

#include "src/KDTree.h"

#include "src/sphere.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "src/Ball.h"
#include "src/Wall.h"

GLFWwindow *window;

// Include GLM

using namespace glm;
using namespace std;

#include "src/shader.hpp"

int main(void) {

  // Initialise GLFW
  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    getchar();
    return -1;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS
  // happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Open a window and create its OpenGL context
  window = glfwCreateWindow(1024, 768, "Bouncing balls", NULL, NULL);
  if (window == NULL) {
    fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, "
                    "they are not 3.3 compatible. Try the 2.1 version of the "
                    "tutorials.\n");
    getchar();
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // Initialize GLEW
  glewExperimental = true; // Needed for core profile
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    getchar();
    glfwTerminate();
    return -1;
  }

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // Dark blue background
  glClearColor(0.7f, 0.3f, 0.4f, 0.0f);

  unsigned int programID = LoadShaders("StandardShading.vertexshader",
                                       "StandardShading.fragmentshader");
  int ViewMatrixID = glGetUniformLocation(programID, "V");
  int MatrixID = glGetUniformLocation(programID, "VP");

  Sphere sfera(programID);

  glUseProgram(programID);
  int LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  do {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f),
                                            (float)4 / (float)3, 0.1f, 1000.0f);

    glm::mat4 View = glm::lookAt(
        glm::vec3(0, 0, 10), // Camera is at (0,0,50), in World Space
        glm::vec3(0, 0, -1), // and looks at the origin
        glm::vec3(0, 1, 0)   // Head is up (set to 0,-1,0 to look upside-down)
        );

    glm::mat4 VP = Projection * View;

    glm::vec3 lightPos = glm::vec3(0, 0, 20);
    glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &VP[0][0]);

    glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);
    sfera.drawSphere(1, 0, 0, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();

  } // Check if the ESC key was pressed or the window was closed
  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         glfwWindowShouldClose(window) == 0);

  // Close OpenGL window and terminate GLFW
  glfwTerminate();

  return 0;
}
