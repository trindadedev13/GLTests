#include "Graphics/BrutColor.hpp"

#include <stdint.h>

namespace Brut {

Color::Color() : r{1.0f}, g{1.0f}, b{1.0f}, a{1.0f} {}

Color::Color(float r, float g, float b, float a) : r{r}, g{g}, b{b}, a{a} {}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  this->r = r / 255.0f;
  this->g = g / 255.0f;
  this->b = b / 255.0f;
  this->a = a / 255.0f;
}

const Color Color::White = {1.0f, 1.0f, 1.0f, 1.0f};
const Color Color::Black = {0.0f, 0.0f, 0.0f, 1.0f};
const Color Color::Red = {1.0f, 0.0f, 1.0f, 1.0f};
const Color Color::Green = {0.0f, 1.0f, 0.0f, 1.0f};
const Color Color::Blue = {0.0f, 0.0f, 1.0f, 1.0f};
const Color Color::Yellow = {1.0f, 1.0f, 0.1f, 1.0f};
const Color Color::Cyan = {0.0f, 1.0f, 1.0f, 1.0f};
const Color Color::Magenta = {1.0f, 0.0f, 1.0f, 1.0f};

}  // namespace Brut