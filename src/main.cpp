#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "BrutGame.hpp"

int main() {
  Brut::Game game{};
  try {
    game.run();
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}