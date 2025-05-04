#ifndef COLOR_H
#define COLOR_H

typedef struct {
  float r;
  float g;
  float b;
  float a;
} color;

color mkncolor(float r, float g, float b, float a);

color mk8bcolor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

extern const color COLOR_WHITE;
extern const color COLOR_BLACK;
extern const color COLOR_RED;
extern const color COLOR_GREEN;
extern const color COLOR_BLUE;

#endif