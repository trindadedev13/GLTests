#include "Objects/Primitives/BrutCubeCollection.hpp"

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Buffer/BrutBuffer.hpp"
#include "Graphics/BrutColor.hpp"

namespace Brut {

CubeCollection::CubeCollection(unsigned int _cubeCount)
    : cubeCount(_cubeCount) {
  initCubeCollection();
}

CubeCollection::~CubeCollection() {}

void CubeCollection::initCubeCollection() {
  fillBuffers();
  linkBuffers();
}

void CubeCollection::fillBuffers() {
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

  verticesVBO.bind();
  verticesVBO.putData(vertices, sizeof(vertices));

  modelVBO.bind();
  modelVBO.putData(0, cubeCount * sizeof(glm::mat4), GL_DYNAMIC_DRAW);

  colorVBO.bind();
  colorVBO.putData(0, cubeCount * sizeof(Color), GL_DYNAMIC_DRAW);
}

void CubeCollection::linkBuffers() {
  VAO.bind();
  {
    EBO.bind();
    verticesVBO.bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    colorVBO.bind();
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribDivisor(1, 1);

    modelVBO.bind();
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4),
                          (void*)(sizeof(glm::vec4) * 0));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4),
                          (void*)(sizeof(glm::vec4) * 1));

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4),
                          (void*)(sizeof(glm::vec4) * 2));

    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4),
                          (void*)(sizeof(glm::vec4) * 3));

    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
  }
  VAO.unbind();
}

void CubeCollection::setModels(const std::vector<glm::mat4>& models) {
  modelVBO.bind();
  modelVBO.subData(models.data(), models.size() * sizeof(glm::mat4));
}

void CubeCollection::setColors(const std::vector<Color>& colors) {
  colorVBO.bind();
  colorVBO.subData(colors.data(), colors.size() * sizeof(Color));
}

void CubeCollection::draw() {
  VAO.bind();
  { glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, cubeCount); }
  VAO.unbind();
}

}  // namespace Brut