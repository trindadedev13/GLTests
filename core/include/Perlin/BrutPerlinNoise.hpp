#ifndef BRUT_PERLIN_NOISE_HPP
#define BRUT_PERLIN_NOISE_HPP

#include <vector>

namespace Brut {

class PerlinNoise {
 public:
  PerlinNoise(unsigned int seed = 0);
  double noise(double x, double y, double z) const;

 private:
  std::vector<int> p;
  double fade(double t) const;
  double lerp(double t, double a, double b) const;
  double grad(int hash, double x, double y, double z) const;
};

}  // namespace Brut

#endif