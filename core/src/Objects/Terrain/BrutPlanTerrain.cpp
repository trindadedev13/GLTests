#include "Objects/Terrain/BrutPlanTerrain.hpp"

#include <cmath>
#include <cstdlib>
#include <vector>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Graphics/BrutColor.hpp"
#include "Objects/Primitives/BrutCubeCollection.hpp"

namespace Brut {

PlanTerrain::PlanTerrain(int width, int depth, float cubeSize)
    : width(width), depth(depth), cubeSize(cubeSize) {}

PlanTerrain::~PlanTerrain() {}

void PlanTerrain::generate() {
  unsigned int totalCubes = width * depth * 2;

  cubeCollection = std::make_unique<CubeCollection>(totalCubes);
  std::vector<glm::mat4> models(totalCubes);
  std::vector<Color> colors(totalCubes);

  int i = 0;
  for (int x = 0; x < width; ++x) {
    for (int z = 0; z < depth; ++z) {
      for (int y = 0; y < 2; ++y) {
        glm::vec3 pos = glm::vec3(x, y, z);
        models[i] = glm::translate(glm::mat4(1.0f), pos * cubeSize) *
                    glm::scale(glm::mat4(1.0f), glm::vec3(cubeSize));
        if (y >= 1) {
          colors[i] = Color::Brown;
        } else {
          colors[i] = Color::Green;
        }
        ++i;
      }
    }
  }

  cubeCollection->setModels(models);
  cubeCollection->setColors(colors);
}

void PlanTerrain::draw() {
  cubeCollection->draw();
}

float PlanTerrain::getCubeSize() const {
  return cubeSize;
}

}  // namespace Brut