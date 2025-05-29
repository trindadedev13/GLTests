#ifndef BRUT_GAME_HPP
#define BRUT_GAME_HPP

#include <string>

#include "BrutConfig.h"
#include "BrutGameClock.hpp"
#include "Assets/BrutIAssetsManager.hpp"
#include "Camera/BrutCamera.hpp"
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
  /** The game window. Requires each platform implementation (see
   * BrutIWindow.hpp). */
  IWindow* window;
  /** The game assets manager */
  IAssetsManager* assetsManager;
  /** Stores all shaders by name */
  ShadersManager shadersManager;
  /** The clock counts from the start of the game. */
  GameClock gameClock{};
  /** Game Player */
  Player player{};
  /** Game Camera. */
  Camera camera;
  /** The fov */
  /** true if ctrl is pressed. */
  bool ctrl{false};
};

}  // namespace Brut

#endif
