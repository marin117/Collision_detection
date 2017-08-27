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
using namespace std;

#define stacks 20
#define slices 20
#define radius 1

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
  unsigned int programID = LoadShaders("SimpleVertexShader.vertexshader",
                                       "SimpleFragmentShader.fragmentshader");
  int MatrixID = glGetUniformLocation(programID, "MVP");
  GLuint vao;
  GLuint ebo;
  GLuint vbo;
  std::vector<glm::vec3> vertices;
  std::vector<int> indices;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  for (int i = 0; i <= stacks; ++i) {

    GLfloat V = i / (float)stacks;
    GLfloat phi = V * glm::pi<float>();

    // Loop Through Slices
    for (int j = 0; j <= slices; ++j) {

      GLfloat U = j / (float)slices;
      GLfloat theta = U * (glm::pi<float>() * 2);

      // Calc The Vertex Positions
      GLfloat x = cosf(theta) * sinf(phi);
      GLfloat y = cosf(phi);
      GLfloat z = sinf(theta) * sinf(phi);

      // Push Back Vertex Data
      vertices.push_back(glm::vec3(x, y, z));
    }
  }

  // Calc The Index Positions
  for (int i = 0; i < slices * stacks + slices; ++i) {

    indices.push_back(i);
    indices.push_back(i + slices + 1);
    indices.push_back(i + slices);

    indices.push_back(i + slices + 1);
    indices.push_back(i);
    indices.push_back(i + 1);
  }

  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
               &indices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat) * 3,
               &vertices[0], GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glEnableVertexAttribArray(0);
  float i = 0.1;

  do {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f),
                                            (float)4 / (float)3, 0.1f, 1000.0f);

    glm::mat4 View = glm::lookAt(
        glm::vec3(0, 0, 50), // Camera is at (0,0,50), in World Space
        glm::vec3(0, 0, -1), // and looks at the origin
        glm::vec3(0, 1, 0)   // Head is up (set to 0,-1,0 to look upside-down)
        );
    glm::mat4 Model = glm::mat4(1.0);
    glm::vec3 rad = glm::vec3(1.0f, 1.0f, 1.0f) * 2.0f;
    Model = glm::scale(Model, rad);
    glm::vec3 pos = glm::vec3(1.0f, i -= 0.05, 0.0);
    Model = glm::translate(Model, pos);
    glm::mat4 MVP = Projection * View * Model;
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

    glUseProgram(programID);

    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL);

    glfwSwapBuffers(window);
    glfwPollEvents();

  } // Check if the ESC key was pressed or the window was closed
  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         glfwWindowShouldClose(window) == 0);

  // Close OpenGL window and terminate GLFW
  glfwTerminate();

  return 0;
}
