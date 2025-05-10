#ifndef BRUT_GAME_HPP
#define BRUT_GAME_HPP

#include <string>

#include "BrutWindow.hpp"
#include "config.h"
#include "Graphics/Shader/BrutShadersManager.hpp"

namespace Brut {

class Game {
 public:
  Game();
  ~Game();

  void run();

 private:
  Window window{GL_WINDOW_WIDTH, GL_WINDOW_HEIGHT, GL_WINDOW_NAME};
  ShadersManager shadersManager{std::string(BRUT_RUNNING_PATH) + "/shaders/"};
};

}  // namespace Brut

#endif