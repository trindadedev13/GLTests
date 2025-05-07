#include "graphics/color.h"

#include <stdint.h>

const color COLOR_WHITE = {1.0f, 1.0f, 1.0f, 1.0f};
const color COLOR_BLACK = {0.0f, 0.0f, 0.0f, 0.0f};
const color COLOR_RED = {1.0f, 0.0f, 0.0f, 1.0f};
const color COLOR_GREEN = {0.0f, 1.0f, 0.0f, 1.0f};
const color COLOR_BLUE = {0.0f, 0.0f, 1.0f, 1.0f};

color mkcolor(float r, float g, float b, float a) {
  return (color){.r = r, .g = g, .b = b, .a = a};
}

color mk8bcolor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  return (color){
      .r = r / 255.0f, .g = g / 255.0f, .b = b / 255.0f, .a = a / 255.0f};
}