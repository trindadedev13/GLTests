#ifndef BRUT_TERRAIN_HPP
#define BRUT_TERRAIN_HPP

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "Graphics/Shader/BrutShader.hpp"
#include "Objects/Primitives/BrutCube.hpp"

namespace Brut {

class Terrain {
 public:
  Terrain(int width, int depth, float cubeSize = 1.0f);
  ~Terrain();

  void draw(Shader& shader, const glm::mat4& view);
  void generate(float frequency = 0.1f, int seed = 0);

  const std::vector<std::unique_ptr<Cube>>& getCubes() const;

  float getCubeSize() const;

 private:
  int width, depth;
  float cubeSize;
  std::vector<std::unique_ptr<Cube>> cubes;
};

}  // namespace Brut

#endif