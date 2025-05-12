#ifndef BRUT_TERRAIN_HPP
#define BRUT_TERRAIN_HPP

#include <vector>

#include "Buffer/BrutBuffer.hpp"
#include "Buffer/BrutVertexArrayBuffer.hpp"
#include "Graphics/BrutColor.hpp"
#include "Objects/Primitives/BrutObject.hpp"

namespace Brut {

class Terrain : public Object {
 public:
  Terrain(float side = 50.0f);
  ~Terrain();

  Color color{Color::White};

  void draw() override;
  void setColor(Color color);

 private:
  float side;
  unsigned int totalIndices;
  std::vector<Color> colors{};

  void initTerrain();
  void fillBuffers();
  void linkBuffers();
};

}  // namespace Brut

#endif