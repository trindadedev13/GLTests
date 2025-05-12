#ifndef BRUT_PYRAMID_HPP
#define BRUT_PYRAMID_HPP

#include <array>

#include "Graphics/BrutColor.hpp"
#include "Objects/Primitives/BrutObject.hpp"

namespace Brut {

class Pyramid : public Object {
 public:
  Pyramid();
  ~Pyramid();

  std::array<Color, 5> faceColors = {Color::White, Color::White, Color::White,
                                     Color::White, Color::White};

  void draw() override;

  void setColors(const std::array<Color, 5>& faceColors);

 private:
  void initPyramid();
  void fillBuffers();
  void linkBuffers();
};

}  // namespace Brut

#endif