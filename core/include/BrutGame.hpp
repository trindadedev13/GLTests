#ifndef BRUT_GAME_HPP
#define BRUT_GAME_HPP

#include <string>

#include "BrutConfig.hpp"
#include "BrutGameClock.hpp"
#include "BrutIWindow.hpp"
#include "Graphics/Shader/BrutShadersManager.hpp"

namespace Brut {

class Game {
 public:
  Game(IWindow* window);
  ~Game();

  void run();

 private:
  IWindow* window;
  ShadersManager shadersManager{std::string(BRUT_RUNNING_PATH) + "/shaders/"};
  GameClock gameClock{};
};

}  // namespace Brut

#endif