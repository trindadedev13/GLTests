#ifndef BRUT_GAME_HPP
#define BRUT_GAME_HPP

#include "BrutWindow.hpp"
#include "config.h"

namespace Brut {
class Game {
 public:
  Game();
  ~Game();

  void run();

 private:
  Window window{GL_WINDOW_WIDTH, GL_WINDOW_HEIGHT, GL_WINDOW_NAME};
};
}  // namespace Brut

#endif