#include "Objects/BrutCube.hpp"

#include <array>

#include <glad/gl.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Buffer/BrutBuffer.hpp"
#include "Graphics/BrutColor.hpp"

namespace Brut {

Cube::Cube()
    : VAO{}, EBO{}, positionVBO{}, colorVBO{}, position{0.f}, model{1.f} {
  initCube();
}

Cube::~Cube() {}

void Cube::initCube() {
  fillBuffers();
  linkBuffers();
}

void Cube::fillBuffers() {
  glm::vec3 points[] = {
      // Front
      glm::vec3(-0.5f, +0.5f, +0.5f),  // 0
      glm::vec3(-0.5f, -0.5f, +0.5f),  // 1
      glm::vec3(+0.5f, -0.5f, +0.5f),  // 2
      glm::vec3(+0.5f, +0.5f, +0.5f),  // 3

      // Back
      glm::vec3(+0.5f, +0.5f, -0.5f),  // 4
      glm::vec3(+0.5f, -0.5f, -0.5f),  // 5
      glm::vec3(-0.5f, -0.5f, -0.5f),  // 6
      glm::vec3(-0.5f, +0.5f, -0.5f),  // 7

  };
  glm::vec3 vertices[] = {
      // Front
      points[0],  // 0
      points[1],  // 1
      points[2],  // 2
      points[3],  // 3

      // Back
      points[4],  // 4
      points[5],  // 5
      points[6],  // 6
      points[7],  // 7

      // Right
      points[3],  // 8
      points[2],  // 9
      points[5],  // 10
      points[4],  // 11

      // Left
      points[7],  // 12
      points[6],  // 13
      points[1],  // 14
      points[0],  // 15

      // Top
      points[7],  // 16
      points[0],  // 17
      points[3],  // 18
      points[4],  // 19

      // Bottom
      points[1],  // 20
      points[6],  // 21
      points[5],  // 22
      points[2]   // 23
  };

  unsigned int indices[] = {
      0,  1,  2,  0,  2,  3,   // Front
      4,  5,  6,  4,  6,  7,   // Back
      8,  9,  10, 8,  10, 11,  // Right
      12, 13, 14, 12, 14, 15,  // Left
      16, 17, 18, 16, 18, 19,  // Top
      20, 21, 22, 20, 22, 23   // Bottom
  };

  EBO.bind();
  EBO.putData(indices, sizeof(indices));

  positionVBO.bind();
  positionVBO.putData(vertices, sizeof(vertices));

  // Fill cube with color
  setColors(faceColors);
}

void Cube::linkBuffers() {
  VAO.bind();
  {
    EBO.bind();
    positionVBO.bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    colorVBO.bind();
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
  }
  VAO.unbind();
}

void Cube::setPosition(float x, float y, float z) {
  position = glm::vec3(x, y, z);
  updatePosition();
}

glm::mat4 Cube::getPosition() const {
  return model;
}

void Cube::draw() {
  VAO.bind();
  {
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
  }
  VAO.unbind();
}

void Cube::updatePosition() {
  model = glm::translate(glm::mat4(1.f), position);
}

void Cube::setColors(const std::array<Color, 6>& newFaceColors) {
  Color vertexColors[24] = {};

  for (int face = 0; face < 6; ++face) {
    faceColors[face] = newFaceColors[face];
    for (int i = 0; i < 4; ++i) {
      vertexColors[face * 4 + i] = faceColors[face];
    }
  }

  colorVBO.bind();
  colorVBO.putData(vertexColors, sizeof(vertexColors));
}

}  // namespace Brut