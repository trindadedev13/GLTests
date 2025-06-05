#ifndef BRUT_PLAN_TERRAIN_HPP
#define BRUT_PLAN_TERRAIN_HPP

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "Graphics/Shader/BrutShader.hpp"
#include "Objects/Primitives/BrutCubeCollection.hpp"

namespace Brut {

class PlanTerrain {
 public:
  PlanTerrain(int width, int depth, float cubeSize = 1.0f);
  ~PlanTerrain();

  void draw();
  void generate();

  float getCubeSize() const;

 private:
  int width, depth;
  float cubeSize;
  std::unique_ptr<CubeCollection> cubeCollection;
};

}  // namespace Brut

#endif