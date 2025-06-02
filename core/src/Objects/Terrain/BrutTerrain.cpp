#include "Objects/Terrain/BrutTerrain.hpp"

#include <cmath>
#include <cstdlib>
#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "Graphics/Shader/BrutShader.hpp"
#include "Objects/Primitives/BrutCube.hpp"
#include "Perlin/BrutPerlinNoise.hpp"

namespace Brut {

Terrain::Terrain(int width, int depth, float cubeSize)
    : width(width), depth(depth), cubeSize(cubeSize) {}

Terrain::~Terrain() {}

void Terrain::generate(float frequency, int seed) {
  cubes.clear();

  PerlinNoise noise(seed);

  for (int x = 0; x < width; ++x) {
    for (int z = 0; z < depth; ++z) {
      float heightNoise = noise.noise(x * frequency, z * frequency, 0.0);
      int height =
          static_cast<int>((heightNoise + 1.0) * 0.5 * 5);  // Altura máxima = 5

      for (int y = 0; y <= height; ++y) {
        auto cube = std::make_unique<Cube>();
        cube->setPosition(glm::vec3(x * cubeSize, y * cubeSize, z * cubeSize));

        // Cor diferente no topo
        if (y == height) {
          cube->setColors({Color::Green, Color::Green, Color::Green,
                           Color::Green, Color::Green, Color::Green});
        } else {
          cube->setColors({Color::Brown, Color::Brown, Color::Brown,
                           Color::Brown, Color::Brown, Color::Brown});
        }

        cubes.push_back(std::move(cube));
      }
    }
  }
}

void Terrain::draw(Shader& shader, const glm::mat4& view) {
  for (auto& cube : cubes) {
    glm::mat4 model = cube->getPosition();
    shader.bind();
    shader.sendUniformData("model", model);
    shader.sendUniformData("view", view);
    cube->draw();
    shader.unbind();
  }
}

const std::vector<std::unique_ptr<Cube>>& Terrain::getCubes() const {
  return cubes;
}

float Terrain::getCubeSize() const {
  return cubeSize;
}

}  // namespace Brut