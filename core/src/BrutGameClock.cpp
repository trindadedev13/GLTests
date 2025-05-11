#include "BrutGameClock.hpp"

#include <chrono>

namespace Brut {

GameClock::GameClock() {
  startTime = std::chrono::high_resolution_clock::now();
}

double GameClock::getTime() const {
  auto current = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = current - startTime;
  return elapsed.count();
}

}  // namespace Brut