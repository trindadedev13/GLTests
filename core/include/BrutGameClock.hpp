#ifndef BRUT_GAME_CLOCK_HPP
#define BRUT_GAME_CLOCK_HPP

#include <chrono>

namespace Brut {

class GameClock {
 public:
  GameClock();
  double getTime() const;

 private:
  std::chrono::high_resolution_clock::time_point startTime;
};

}  // namespace Brut

#endif