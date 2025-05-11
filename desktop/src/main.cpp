#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "BrutDesktopWindow.hpp"
#include "BrutGame.hpp"
#include "BrutWindowConfig.hpp"

int main() {
  Brut::DesktopWindow window{GL_WINDOW_WIDTH, GL_WINDOW_HEIGHT, GL_WINDOW_NAME};
  Brut::Game game{&window};
  try {
    game.run();
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}