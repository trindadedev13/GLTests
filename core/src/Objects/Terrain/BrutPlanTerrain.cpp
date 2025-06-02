#include "Objects/Terrain/BrutPlanTerrain.hpp"

#include <cmath>
#include <cstdlib>
#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "Graphics/Shader/BrutShader.hpp"
#include "Objects/Primitives/BrutCube.hpp"

namespace Brut {

PlanTerrain::PlanTerrain(int width, int depth, float cubeSize)
    : width(width), depth(depth), cubeSize(cubeSize) {}

PlanTerrain::~PlanTerrain() {}

void PlanTerrain::generate() {
  cubes.clear();

  for (int x = 0; x < width; ++x) {
    for (int z = 0; z < depth; ++z) {
      for (int y = 0; y < 2; ++y) {
        auto cube = std::make_unique<Cube>();
        cube->setPosition(glm::vec3(x * cubeSize, y * cubeSize, z * cubeSize));

        if (y == 1) {
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

void PlanTerrain::draw(Shader& shader, const glm::mat4& view) {
  for (auto& cube : cubes) {
    glm::mat4 model = cube->getPosition();
    shader.bind();
    shader.sendUniformData("model", model);
    shader.sendUniformData("view", view);
    cube->draw();
    shader.unbind();
  }
}

const std::vector<std::unique_ptr<Cube>>& PlanTerrain::getCubes() const {
  return cubes;
}

float PlanTerrain::getCubeSize() const {
  return cubeSize;
}

}  // namespace Brut