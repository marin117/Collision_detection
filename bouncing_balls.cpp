// Include standard headers

#include "src/KDTree.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <GL/glew.h>

// Include GLFW
#include "src/Ball.h"
#include "src/Wall.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
GLFWwindow *window;

// Include GLM

using namespace glm;

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

  // Create and compile our GLSL program from the shaders
  unsigned int programID = LoadShaders("StandardShading.vertexshader",
                                       "StandardShading.fragmentshader");
  int MatrixID = glGetUniformLocation(programID, "VP");
  int ViewMatrixID = glGetUniformLocation(programID, "V");

  Sphere sphere(programID);

  glUseProgram(programID);
  int LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

  std::vector<Wall> walls;
  KDtreeNode<Wall> wallsKDtree;
  KDtreeNode<Ball> ballsKDtree;
  // walls.emplace_back(Wall(0, 20, 0, 25, 0, 0, 0, -1, 0, 10000));
  walls.emplace_back(Wall(0, -40, 0, 25000, 0, 0, 0, 1, 0, 10000));
  walls.emplace_back(Wall(46, 0, 0, 0, 25000, 0, -1, 0, 0, 10000));
  walls.emplace_back(Wall(-46, 0, 0, 0, 25000, 0, 1, 0, 0, 10000));

  std::vector<Ball> balls;

  for (uint i = 0; i < 100; i++) {
    float x = std::rand() % 40 - 20;
    float y = std::rand() % 20;

    float speedX = std::rand() % 20 - 10;
    float speedY = std::rand() % 10 + 1;
    float mass = std::rand() % 20 + 40;
    balls.emplace_back(Ball(x, y, 0, 1.0f, speedX, speedY, 0.0, mass, i));
  }

  // balls.emplace_back(Ball(20, 0, 0, 1.0f, 2.0, 0.0, 0.0, 1, 0));

  double lastTime;
  double dt, currentTime;
  wallsKDtree.build_tree(walls, 0);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  do {
    currentTime = glfwGetTime();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f),
                                            (float)4 / (float)3, 0.1f, 1000.0f);

    glm::mat4 View = glm::lookAt(
        glm::vec3(0, 0, 100), // Camera is at (0,0,50), in World Space
        glm::vec3(0, 0, -1),  // and looks at the origin
        glm::vec3(0, 1, 0)    // Head is up (set to 0,-1,0 to look upside-down)
        );

    glm::mat4 VP = Projection * View;

    glm::vec3 lightPos = glm::vec3(0, 0, 20);
    glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &VP[0][0]);

    glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);

    for (uint i = 0; i < balls.size(); i++)
      balls[i].drawSphere(sphere);

    ballsKDtree.build_tree(balls, 0);

    for (uint i = 0; i < balls.size(); i++) {
      wallsKDtree.searchCollisions(balls[i]);
    }
    for (uint i = 0; i < balls.size(); i++) {
      ballsKDtree.searchCollisions(balls[i]);
    }
    ballsKDtree.treeTraverse();
    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
    for (uint i = 0; i < balls.size(); i++) {
      balls[i].updatePosition(dt);
    }

    dt = currentTime - lastTime;
    lastTime = currentTime;

  } // Check if the ESC key was pressed or the window was closed
  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         glfwWindowShouldClose(window) == 0);

  // Close OpenGL window and terminate GLFW
  glfwTerminate();

  return 0;
}
