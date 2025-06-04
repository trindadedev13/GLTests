#ifndef BRUT_TERRAIN_HPP
#define BRUT_TERRAIN_HPP

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "Objects/Primitives/BrutCubeCollection.hpp"

namespace Brut {

class Terrain {
 public:
  Terrain(int width, int depth, float cubeSize = 1.0f);
  ~Terrain();

  void draw();
  void generate(float frequency = 0.1f, int seed = 0);

  float getCubeSize() const;

 private:
  int width, depth;
  float cubeSize;
  std::unique_ptr<CubeCollection> cubeCollection;
};

}  // namespace Brut

#endif