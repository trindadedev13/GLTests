#include "Perlin/BrutPerlinNoise.hpp"

#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>

namespace Brut {

PerlinNoise::PerlinNoise(unsigned int seed) {
  p.resize(256);
  std::iota(p.begin(), p.end(), 0);
  std::default_random_engine engine(seed);
  std::shuffle(p.begin(), p.end(), engine);
  p.insert(p.end(), p.begin(), p.end());
}

double PerlinNoise::fade(double t) const {
  return t * t * t * (t * (t * 6 - 15) + 10);
}

double PerlinNoise::lerp(double t, double a, double b) const {
  return a + t * (b - a);
}

double PerlinNoise::grad(int hash, double x, double y, double z) const {
  int h = hash & 15;
  double u = h < 8 ? x : y;
  double v = h < 4 ? y : (h == 12 || h == 14 ? x : z);
  return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
}

double PerlinNoise::noise(double x, double y, double z) const {
  int X = (int)floor(x) & 255;
  int Y = (int)floor(y) & 255;
  int Z = (int)floor(z) & 255;

  x -= floor(x);
  y -= floor(y);
  z -= floor(z);

  double u = fade(x), v = fade(y), w = fade(z);
  int A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z;
  int B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;

  return lerp(
      w,
      lerp(v, lerp(u, grad(p[AA], x, y, z), grad(p[BA], x - 1, y, z)),
           lerp(u, grad(p[AB], x, y - 1, z), grad(p[BB], x - 1, y - 1, z))),
      lerp(v,
           lerp(u, grad(p[AA + 1], x, y, z - 1),
                grad(p[BA + 1], x - 1, y, z - 1)),
           lerp(u, grad(p[AB + 1], x, y - 1, z - 1),
                grad(p[BB + 1], x - 1, y - 1, z - 1))));
}

}  // namespace Brut