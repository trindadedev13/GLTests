#include "BrutGame.hpp"

#include <iostream>
#include <memory>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL3/SDL.h>

#include "BrutConfig.h"
#include "Assets/BrutIAssetsManager.hpp"
#include "Camera/BrutCamera.hpp"
#include "Error/BrutError.hpp"
#include "FreeTypeGL/BrutFreeTypeGL.hpp"
#include "Graphics/BrutColor.hpp"
#include "Graphics/Shader/BrutShader.hpp"
#include "Objects/Terrain/BrutPlanTerrain.hpp"
#include "Window/BrutIWindow.hpp"

namespace Brut {

Game::Game(IWindow* _window, IAssetsManager* _assetsManager)
    : window(_window),
      assetsManager(_assetsManager),
      camera(window->width, window->height) {
  shadersManager = std::make_shared<ShadersManager>(_assetsManager);
  fontRenderer = std::make_shared<Ftgl::FontRenderer>(
      shadersManager, assetsManager, window->width, window->height);
}

Game::~Game() {}

void Game::inputs() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_EVENT_QUIT:
        window->close();
        break;

      case SDL_EVENT_KEY_DOWN:
      case SDL_EVENT_KEY_UP: {
        bool isPressed = event.key.down;
        SDL_Keycode keycode = event.key.key;

        switch (keycode) {
          case SDLK_ESCAPE:
            if (isPressed)
              window->close();
            break;

          case SDLK_W:
          case SDLK_UP:
            if (isPressed)
              player.moveForward();
            break;

          case SDLK_A:
          case SDLK_LEFT:
            if (isPressed)
              player.moveLeft();
            break;

          case SDLK_S:
          case SDLK_DOWN:
            if (isPressed)
              player.moveBack();
            break;

          case SDLK_D:
          case SDLK_RIGHT:
            if (isPressed)
              player.moveRight();
            break;

          case SDLK_LCTRL:
          case SDLK_RCTRL:
            ctrl = isPressed;
            break;

          case SDLK_SPACE:
            player.jump();
            break;

          default:
            break;
        }
        break;
      }

      case SDL_EVENT_MOUSE_MOTION: {
        if (!ctrl) {
          glm::vec2 mousePos(event.motion.x, event.motion.y);
          player.mouseUpdate(mousePos);
        }
        break;
      }

      default:
        break;
    }
  }
}

void Game::run() {
  auto defShaderOp = shadersManager->get("defShader");

  if (!defShaderOp)
    fatalError("Default shader not found");

  auto defShader = *defShaderOp;

  glm::mat4 perspectiveProjection = camera.getPerspectiveProjectionMatrix();

  player.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

  defShader->bind();
  defShader->sendUniformData("projection", perspectiveProjection);
  defShader->unbind();

  PlanTerrain terrain{16, 16};
  // terrain.generate(0.1f, 123.0f);
  terrain.generate();

  float startTime = gameClock.getTime();
  float lastTime = gameClock.getTime();
  int frames = 0;

  std::string fpsText = "FPS: 0";
  while (window->isRunning()) {
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, window->width, window->height);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glClearColor(0.40f, 0.65f, 0.85f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float currentTime = gameClock.getTime();
    frames++;

    camera.followPlayer(player);

    player.update();

    glm::mat4 viewMatrix = camera.getViewMatrix();
    defShader->bind();
    defShader->sendUniformData("view", viewMatrix);
    defShader->unbind();

    if (currentTime - lastTime >= 1.0f) {
      fpsText = "FPS: " + std::to_string(std::max(frames, 1));
      frames = 0;
      lastTime = currentTime;
    }

    // terrain
    defShader->bind();
    terrain.draw();

    // render FPS
    fontRenderer->renderText(Ftgl::FONT_TYPE_LIBERASTIKA, Color::White,
                             glm::vec2(10, window->height - 64 - 60), fpsText);

    inputs();

    window->swapBuffers();
  }
}

}  // namespace Brut
