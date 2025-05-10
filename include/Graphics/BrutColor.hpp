#ifndef BRUT_COLOR_HPP
#define BRUT_COLOR_HPP

#include <stdint.h>

namespace Brut {

class Color {
 public:
  Color();
  Color(float r, float g, float b, float a);
  Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

  float r;
  float g;
  float b;
  float a;

  static const Color White;
  static const Color Black;
  static const Color Red;
  static const Color Green;
  static const Color Blue;
  static const Color Yellow;
  static const Color Cyan;
  static const Color Magenta;
};

}  // namespace Brut
#endif