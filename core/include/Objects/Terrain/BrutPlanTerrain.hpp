#ifndef BRUT_PLAN_TERRAIN_HPP
#define BRUT_PLAN_TERRAIN_HPP

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "Graphics/Shader/BrutShader.hpp"
#include "Objects/Primitives/BrutCube.hpp"

namespace Brut {

class PlanTerrain {
 public:
  PlanTerrain(int width, int depth, float cubeSize = 1.0f);
  ~PlanTerrain();

  void draw(Shader& shader, const glm::mat4& view);
  void generate();

  const std::vector<std::unique_ptr<Cube>>& getCubes() const;

  float getCubeSize() const;

 private:
  int width, depth;
  float cubeSize;
  std::vector<std::unique_ptr<Cube>> cubes;
};

}  // namespace Brut

#endif