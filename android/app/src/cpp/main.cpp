#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "BrutAndroidWindow.hpp"
#include "BrutGame.hpp"

int main(void) {
  Brut::AndroidWindow window{0, 0, "Brut"};
  Brut::Game game{&window};
  try {
    game.run();
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}