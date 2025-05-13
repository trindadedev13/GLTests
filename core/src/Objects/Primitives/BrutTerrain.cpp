#include "Objects/Primitives/BrutTerrain.hpp"

#include <vector>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Buffer/BrutBuffer.hpp"
#include "Graphics/BrutColor.hpp"

namespace Brut {

Terrain::Terrain(float side) : side{side}, totalIndices{0} {
  initTerrain();
}

Terrain::~Terrain() {}

void Terrain::initTerrain() {
  fillBuffers();
  linkBuffers();
}

void Terrain::fillBuffers() {
  std::vector<glm::vec3> vertices;
  std::vector<unsigned int> indices;
  float y = -0.5f;
  float increment = 1.0f;

  // row
  for (float z = -side; z <= side; z += increment) {
    // column
    for (float x = -side; x <= side; x += increment) {
      vertices.push_back(glm::vec3(x, y, z));
      colors.push_back(color);
    }
  }

  // Create Indices
  unsigned int columnSize = 2 * static_cast<unsigned int>(side) + 1;

  for (unsigned int row = 0; row < columnSize - 1; row++) {
    for (unsigned int col = 0; col < columnSize - 1; col++) {
      indices.push_back(columnSize * row + col);      // upper left
      indices.push_back(columnSize * row + col + 1);  // upper right

      indices.push_back(columnSize * row + col);               // upper left
      indices.push_back(columnSize * row + col + columnSize);  // bottom left

      indices.push_back(columnSize * row + col + columnSize +
                        1);                                    // bottom right
      indices.push_back(columnSize * row + col + columnSize);  // bottom left

      if (col == columnSize - 2) {
        indices.push_back(columnSize * row + col + 1);  // upper right
        indices.push_back(columnSize * row + col + columnSize +
                          1);  // bottom right
      }
    }
  }

  totalIndices = indices.size();

  EBO.bind();
  EBO.putData(indices.data(), indices.size() * sizeof(unsigned int));

  verticesVBO.bind();
  verticesVBO.putData(vertices.data(), vertices.size() * sizeof(glm::vec3));

  colorVBO.bind();
  colorVBO.putData(colors.data(), colors.size() * sizeof(Color));
}

void Terrain::linkBuffers() {
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

void Terrain::draw() {
  VAO.bind();
  {
    glDrawElements(GL_LINES, totalIndices, GL_UNSIGNED_INT, 0);
  }
  VAO.unbind();
}

void Terrain::setColor(Color newColor) {
  colors.clear();

  float increment = 1.0f;
  unsigned int columnSize = 2 * static_cast<unsigned int>(side) + 1;

  unsigned int totalVertices = columnSize * columnSize;
  for (unsigned int i = 0; i < totalVertices; ++i) {
    colors.push_back(newColor);
  }

  colorVBO.bind();
  colorVBO.putData(colors.data(), colors.size() * sizeof(Color));
}

}  // namespace Brut