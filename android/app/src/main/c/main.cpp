#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "BrutGame.hpp"
#include "Assets/BrutAndroidAssetsManager.hpp"
#include "Assets/jni/brut_android_assets_manager_jni.h"
#include "Window/BrutWindowConfig.h"
#include "Window/BrutSDLWindow.hpp"

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  if (!SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init failed (%s)",
                 SDL_GetError());
    return 1;
  }

  if (!asmgr) {
    if (!SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
                                  "!! ASSET MANAGER IS NULL !!", NULL)) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Assets manager is null");
    }
    SDL_Quit();
    return 1;
  }

  Brut::Android::AssetsManager assetsManager{asmgr};
  Brut::SDLWindow window{GL_WINDOW_WIDTH, GL_WINDOW_HEIGHT, GL_WINDOW_NAME};
  Brut::Game game{&window, &assetsManager};

  try {
    game.run();
  } catch (const std::exception& e) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s\n", e.what());
    SDL_Quit();
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
