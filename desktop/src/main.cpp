#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "BrutDesktopWindow.hpp"
#include "BrutDesktopInputHandler.hpp"
#include "BrutGame.hpp"
#include "BrutWindowConfig.hpp"
#include "Input/BrutInputHandler.hpp"

int main() {
  Brut::DesktopWindow window{GL_WINDOW_WIDTH, GL_WINDOW_HEIGHT, GL_WINDOW_NAME};
  Brut::InputHandler rawInputHandler{};
  Brut::DesktopInputHandler inputHandler{window.glfwWindow, &rawInputHandler};
  Brut::Game game{&window, &rawInputHandler};
  try {
    game.run();
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}