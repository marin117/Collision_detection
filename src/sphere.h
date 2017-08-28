#ifndef _Sphere_h
#define _Sphere_h
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>

using namespace glm;
using namespace std;

class Sphere {

public:
  Sphere(uint Shader) {

    this->shader = Shader;
    this->MatrixID = glGetUniformLocation(Shader, "MVP");
    this->slices = 10;
    this->stacks = 10;
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    for (int i = 0; i <= this->stacks; ++i) {

      GLfloat V = i / (float)this->stacks;
      GLfloat phi = V * glm::pi<float>();

      // Loop Through Slices
      for (int j = 0; j <= this->slices; ++j) {

        GLfloat U = j / (float)this->slices;
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
    for (int i = 0; i < this->slices * this->stacks + this->slices; ++i) {

      indices.push_back(i);
      indices.push_back(i + this->slices + 1);
      indices.push_back(i + this->slices);

      indices.push_back(i + this->slices + 1);
      indices.push_back(i);
      indices.push_back(i + 1);
    }

    glGenBuffers(1, &this->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
                 &this->indices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(GLfloat) * 3,
                 &this->vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
  }

  void drawSphere(float r, float x, float y, float z, glm::mat4 &view,
                  glm::mat4 &projection) {
    glm::mat4 Model = glm::mat4(1.0);
    glm::vec3 rad = glm::vec3(1.0f, 1.0f, 1.0f) * r;
    Model = glm::scale(Model, rad);
    glm::vec3 pos = glm::vec3(x, y, z);
    Model = glm::translate(Model, pos);
    glm::mat4 MVP = projection * view * Model;
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glUseProgram(this->shader);
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL);
  }

private:
  uint vao;
  uint ebo;
  uint vbo;
  std::vector<glm::vec3> vertices;
  std::vector<int> indices;
  uint shader;
  int slices, stacks;
  int MatrixID;
};

#endif
