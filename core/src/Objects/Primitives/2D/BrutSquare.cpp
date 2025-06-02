#include "Objects/Primitives/2D/BrutSquare.hpp"

#include <array>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Graphics/BrutColor.hpp"

namespace Brut {

Square::Square() {
  initSquare();
}

Square::~Square() {}

void Square::initSquare() {
  fillBuffers();
  linkBuffers();
}

void Square::fillBuffers() {
  glm::vec2 vertices[] = {
      // triangle 1
      glm::vec2(0.0f, 1.0f), glm::vec2(0.0f, -1.0f), glm::vec2(1.0f, 0.0f),
      // trangle 2
      glm::vec2(0.0f, 1.0f), glm::vec2(-1.0f, 0.0f), glm::vec2(0.0f, -1.0f)};

  unsigned int indices[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

  EBO.bind();
  EBO.putData(indices, sizeof(indices));

  verticesVBO.bind();
  verticesVBO.putData(vertices, sizeof(vertices));

  setColors(triangleColors);
}

void Square::linkBuffers() {
  VAO.bind();
  {
    EBO.bind();

    verticesVBO.bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    colorVBO.bind();
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
  }
  VAO.unbind();
}

void Square::draw() {
  VAO.bind();
  { glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); }
  VAO.unbind();
}

void Square::setColors(const std::array<Color, 2>& nTriangleColors) {
  for (int i = 0; i < 2; ++i) {
    triangleColors[i] = nTriangleColors[i];
  }
  Color vColors[] = {// triangle 1
                     triangleColors[0], triangleColors[0], triangleColors[0],
                     // triangle 2
                     triangleColors[1], triangleColors[1], triangleColors[1]};
  colorVBO.bind();
  colorVBO.putData(vColors, sizeof(vColors));
}

}  // namespace Brut