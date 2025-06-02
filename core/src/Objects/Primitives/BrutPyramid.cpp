#include "Objects/Primitives/BrutPyramid.hpp"

#include <array>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Graphics/BrutColor.hpp"

namespace Brut {

Pyramid::Pyramid() {
  initPyramid();
}

Pyramid::~Pyramid() {}

void Pyramid::initPyramid() {
  fillBuffers();
  linkBuffers();
}

void Pyramid::fillBuffers() {
  glm::vec3 points[] = {
      glm::vec3(0.0f, 1.0f, 0.0f),   // 0
      glm::vec3(-0.5f, 0.0f, 0.5f),  // 1
      glm::vec3(0.5f, 0.0f, 0.5f),   // 2
      glm::vec3(0.5f, 0.0f, -0.5f),  // 3
      glm::vec3(-0.5f, 0.0f, -0.5f)  // 4
  };

  glm::vec3 vertices[] = {// Front
                          points[0], points[1], points[2],

                          // Right
                          points[0], points[2], points[3],

                          // Left
                          points[0], points[4], points[1],

                          // Back
                          points[0], points[3], points[4],

                          // Bottom
                          points[1], points[4], points[3], points[2]};

  unsigned int indices[] = {// Front
                            0, 1, 2,
                            // Right
                            3, 4, 5,
                            // Left
                            6, 7, 8,
                            // Back
                            9, 10, 11,
                            // Bottom
                            12, 13, 14, 12, 14, 15};

  EBO.bind();
  EBO.putData(indices, sizeof(indices));

  verticesVBO.bind();
  verticesVBO.putData(vertices, sizeof(vertices));

  setColors(faceColors);
}

void Pyramid::linkBuffers() {
  VAO.bind();
  {
    EBO.bind();

    verticesVBO.bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    colorVBO.bind();
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
  }
  VAO.unbind();
}

void Pyramid::draw() {
  VAO.bind();
  { glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0); }
  VAO.unbind();
}

void Pyramid::setColors(const std::array<Color, 5>& nFaceColors) {
  Color vColors[18] = {};
  int v = 0;

  for (int i = 0; i < 5; ++i) {
    faceColors[i] = nFaceColors[i];

    int count =
        (i < 4) ? 3 : 6;  // 3 vertices for lateral vertices, 6 for background
    for (int j = 0; j < count; ++j) {
      vColors[v++] = nFaceColors[i];
    }
  }

  colorVBO.bind();
  colorVBO.putData(vColors, sizeof(vColors));
}

}  // namespace Brut