#ifndef BRUT_GAME_HPP
#define BRUT_GAME_HPP

#include <string>

#include "BrutConfig.hpp"
#include "BrutGameClock.hpp"
#include "BrutIWindow.hpp"
#include "Camera/BrutCamera.hpp"
#include "Graphics/Shader/BrutShadersManager.hpp"
#include "Input/BrutInputHandler.hpp"

namespace Brut {

class Game {
 public:
  Game(IWindow* window, InputHandler* inputHandler);
  ~Game();

  void run();
  void events();

 private:
  IWindow* window;
  ShadersManager shadersManager{std::string(BRUT_RUNNING_PATH) + "/shaders/"};
  GameClock gameClock{};
  Camera camera{};
  InputHandler* inputHandler{};
};

}  // namespace Brut

#endif