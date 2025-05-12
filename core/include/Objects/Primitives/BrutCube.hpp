#ifndef BRUT_CUBE_HPP
#define BRUT_CUBE_HPP

#include <array>

#include <glm/glm.hpp>

#include "Buffer/BrutBuffer.hpp"
#include "Buffer/BrutVertexArrayBuffer.hpp"
#include "Graphics/BrutColor.hpp"
#include "Objects/Primitives/BrutObject.hpp"

namespace Brut {

class Cube : public Object {
 public:
  Cube();
  ~Cube();

  std::array<Color, 6> faceColors = {Color::White, Color::White, Color::White,
                                     Color::White, Color::White, Color::White};

  void draw() override;

  void setColors(const std::array<Color, 6>& newFaceColors);

 private:
  void initCube();
  void fillBuffers();
  void linkBuffers();
};

}  // namespace Brut

#endif