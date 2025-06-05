#include "Objects/Terrain/BrutTerrain.hpp"

#include <cmath>
#include <cstdlib>
#include <vector>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Graphics/BrutColor.hpp"
#include "Objects/Primitives/BrutCubeCollection.hpp"
#include "Perlin/BrutPerlinNoise.hpp"

namespace Brut {

Terrain::Terrain(int width, int depth, float cubeSize)
    : width(width), depth(depth), cubeSize(cubeSize) {}

Terrain::~Terrain() {}

void Terrain::generate(float frequency, int seed) {
  PerlinNoise noise(seed);

  unsigned int totalCubes = width * depth * 2;

  cubeCollection = std::make_unique<CubeCollection>(totalCubes);
  std::vector<glm::mat4> models{};
  std::vector<Color> colors{};

  unsigned int i = 0;
  for (int x = 0; x < width; ++x) {
    for (int z = 0; z < depth; ++z) {
      float heightNoise = noise.noise(x * frequency, z * frequency, 0.0);
      int height =
          static_cast<int>((heightNoise + 1.0) * 0.5 * 5);  // Altura máxima = 5

      for (int y = 0; y <= height; ++y) {
        glm::vec3 pos = glm::vec3(x, y, z);
        models[i] = glm::translate(glm::mat4(1.0f), pos * cubeSize) *
                    glm::scale(glm::mat4(1.0f), glm::vec3(cubeSize));
        if (y >= height) {
          colors[i] = Color::Brown;
        } else {
          colors[i] = Color::Green;
        }
        ++i;
      }
    }
  }
}

void Terrain::draw() {
  cubeCollection->draw();
}

float Terrain::getCubeSize() const {
  return cubeSize;
}

}  // namespace Brut