#ifndef BRUT_TERRAIN_HPP
#define BRUT_TERRAIN_HPP

#include <vector>

#include "Buffer/BrutBuffer.hpp"
#include "Buffer/BrutVertexArrayBuffer.hpp"
#include "Graphics/BrutColor.hpp"

namespace Brut {

class Terrain {
 public:
  Terrain(float side = 50.0f);
  ~Terrain();

  Color color{Color::White};

  void draw();
  void setColor(Color color);

 private:
  VertexArrayBuffer VAO;
  ArrayBuffer verticesVBO;
  ArrayBuffer colorVBO;
  ElementArrayBuffer EBO;
  float side;
  unsigned int totalIndices;
  std::vector<Color> colors{};

  void initTerrain();
  void fillBuffers();
  void linkBuffers();
};

}  // namespace Brut

#endif