#ifndef BRUT_SQUARE_HPP
#define BRUT_SQUARE_HPP

#include <array>

#include "Objects/Primitives/BrutObject.hpp"

#include "Graphics/BrutColor.hpp"

namespace Brut {

class Square : public Object {
 public:
  Square();
  ~Square();

  std::array<Color, 2> triangleColors = {Color::White, Color::White};

  void draw() override;

  void setColors(const std::array<Color, 2>& triangleColors);

 private:
  void initSquare();
  void fillBuffers();
  void linkBuffers();
};

}  // namespace Brut

#endif