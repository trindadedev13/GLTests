#ifndef BRUT_GAME_HPP
#define BRUT_GAME_HPP

#include <memory>
#include <string>

#include "BrutConfig.h"
#include "BrutGameClock.hpp"
#include "Assets/BrutIAssetsManager.hpp"
#include "Camera/BrutCamera.hpp"
#include "FreeTypeGL/BrutFreeTypeGL.hpp"
#include "Graphics/Shader/BrutShadersManager.hpp"
#include "Window/BrutIWindow.hpp"

namespace Brut {

class Game {
 public:
  Game(IWindow* window, IAssetsManager* assetsManager);
  ~Game();

  /** Run the game */
  void run();
  /** Handles all inputs */
  void inputs();

 private:
  /** The game window */
  IWindow* window;
  /** The game assets manager */
  IAssetsManager* assetsManager;
  /** Stores all shaders by name */
  std::shared_ptr<ShadersManager> shadersManager;
  /** The font renderer to draw text */
  std::shared_ptr<Ftgl::FontRenderer> fontRenderer;
  /** The clock counts from the start of the game. */
  GameClock gameClock{};
  /** Game Player */
  Player player{};
  /** Game Camera. */
  Camera camera;
  /** true if ctrl is pressed. */
  bool ctrl{false};
};

}  // namespace Brut

#endif
