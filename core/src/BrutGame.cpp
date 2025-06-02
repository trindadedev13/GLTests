#include "BrutGame.hpp"

#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL3/SDL.h>

#include "BrutConfig.h"
#include "Assets/BrutIAssetsManager.hpp"
#include "Camera/BrutCamera.hpp"
#include "Error/BrutError.hpp"
#include "Graphics/BrutColor.hpp"
#include "Graphics/Shader/BrutShader.hpp"
#include "Objects/Primitives/BrutCube.hpp"
#include "Objects/Primitives/BrutPyramid.hpp"
#include "Objects/Terrain/BrutPlanTerrain.hpp"
#include "Window/BrutIWindow.hpp"

namespace Brut {

Game::Game(IWindow* _window, IAssetsManager* _assetsManager)
    : window(_window),
      assetsManager(_assetsManager),
      shadersManager(_assetsManager),
      camera(window->width, window->height) {}

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
  auto defShaderOp = shadersManager.get("defShader");

  if (!defShaderOp)
    fatalError("Default shader not found");

  Shader& defShader = defShaderOp->get();

  glm::mat4 perspectiveProjection = camera.getPerspectiveProjectionMatrix();

  glEnable(GL_DEPTH_TEST);

  player.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

  Cube cb;
  cb.setPosition(glm::vec3(1.0f, 0.0f, -5.0f));

  defShader.bind();
  defShader.sendUniformData("projection", perspectiveProjection);
  defShader.unbind();

  PlanTerrain terrain{64, 64};
  // terrain.generate(0.1f, 123.0f);
  terrain.generate();

  Pyramid pyramid;
  pyramid.setPosition(glm::vec3(-0.5f, 0.0f, -3.0f));

  float startTime = gameClock.getTime();

  cb.setColors({Color::Red, Color::Green, Color::Blue, Color::Yellow,
                Color::Cyan, Color::Magenta});

  pyramid.setColors(
      {Color::Red, Color::Green, Color::Blue, Color::Yellow, Color::Cyan});

  // terrain.setColor(Color::Blue);

  while (window->isRunning()) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.40f, 0.65f, 0.85f, 1.0f);

    camera.followPlayer(player);

    player.update();

    glm::mat4 viewMatrix = camera.getViewMatrix();

    float currentTime = gameClock.getTime();
    float deltaTime = currentTime - startTime;

    // terrain
    { terrain.draw(defShader, viewMatrix); }

    // cube
    {
      glm::mat4 cubeModel = glm::mat4(1.0f);
      cubeModel =
          glm::rotate(cubeModel, -deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
      cubeModel =
          glm::rotate(cubeModel, 1.75f * deltaTime, glm::vec3(1.f, 0.f, 0.f));
      cubeModel =
          glm::rotate(cubeModel, 0.75f * deltaTime, glm::vec3(0.f, 0.f, 1.f));
      cubeModel = glm::scale(cubeModel, glm::vec3(.5f, .5f, .5f));

      glm::mat4 cubeModelToWorld = cb.getPosition() * cubeModel;
      defShader.bind();
      defShader.sendUniformData("model", cubeModelToWorld);
      defShader.sendUniformData("view", viewMatrix);
      cb.draw();
      defShader.unbind();
    }

    // pyramid
    {
      glm::mat4 pyramidModel = glm::mat4(1.0f);
      pyramidModel =
          glm::rotate(pyramidModel, -deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
      pyramidModel = glm::rotate(pyramidModel, 1.75f * deltaTime,
                                 glm::vec3(1.f, 0.f, 0.f));
      pyramidModel = glm::rotate(pyramidModel, 0.75f * deltaTime,
                                 glm::vec3(0.f, 0.f, 1.f));
      pyramidModel = glm::scale(pyramidModel, glm::vec3(.5f, .5f, .5f));
      glm::mat4 pyramidModelToWorld = pyramid.getPosition() * pyramidModel;
      defShader.bind();
      defShader.sendUniformData("model", pyramidModelToWorld);
      defShader.sendUniformData("view", viewMatrix);
      pyramid.draw();
      defShader.unbind();
    }

    inputs();

    window->swapBuffers();
  }
}

}  // namespace Brut
