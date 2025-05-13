#include "BrutGame.hpp"

#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "BrutConfig.hpp"
#include "BrutIWindow.hpp"
#include "Camera/BrutCamera.hpp"
#include "Graphics/BrutColor.hpp"
#include "Graphics/Shader/BrutShader.hpp"
#include "Input/BrutInputHandler.hpp"
#include "Objects/Primitives/BrutCube.hpp"
#include "Objects/Primitives/BrutPyramid.hpp"
#include "Objects/Primitives/BrutTerrain.hpp"

namespace Brut {

Game::Game(IWindow* _window, InputHandler* _inputHandler)
    : window(_window),
      inputHandler(_inputHandler),
      camera(window->width, window->height) {
  glEnable(GL_DEPTH_TEST);
}

Game::~Game() {}

void Game::inputs() {
  inputHandler->setOnKeyCallback([this](int key, int action) {
    if (key == BRUT_KEY_ESCAPE && action == BRUT_KEY_ACTION_PRESS) {
      window->close();
    } else if ((key == BRUT_KEY_W || key == BRUT_KEY_UP) &&
               (action == BRUT_KEY_ACTION_PRESS ||
                action == BRUT_KEY_ACTION_REPEAT)) {
      camera.moveForward();
    } else if ((key == BRUT_KEY_A || key == BRUT_KEY_LEFT) &&
               (action == BRUT_KEY_ACTION_PRESS ||
                action == BRUT_KEY_ACTION_REPEAT)) {
      camera.moveLeft();
    } else if ((key == BRUT_KEY_S || key == BRUT_KEY_DOWN) &&
               (action == BRUT_KEY_ACTION_PRESS ||
                action == BRUT_KEY_ACTION_REPEAT)) {
      camera.moveBack();
    } else if ((key == BRUT_KEY_D || key == BRUT_KEY_RIGHT) &&
               (action == BRUT_KEY_ACTION_PRESS ||
                action == BRUT_KEY_ACTION_REPEAT)) {
      camera.moveRight();
    } else if (key == BRUT_KEY_LEFT_CTRL || key == BRUT_KEY_RIGHT_CTRL) {
      ctrl = action != BRUT_KEY_ACTION_RELEASE;
    }
  });
  inputHandler->setOnMouseCallback([this](const glm::vec2 position) {
    if (!ctrl)
      camera.mouseUpdate(position);
  });
}

void Game::run() {
  glm::mat4 perspectiveProjection = camera.getPerspectiveProjectionMatrix();

  Shader defShader = shadersManager.get("defShader");
  Shader minorShader = shadersManager.get("minorShader");

  Cube cb;
  cb.setPosition(glm::vec3(1.0f, 0.0f, -5.0f));

  defShader.bind();
  defShader.sendUniformData("projection", perspectiveProjection);
  defShader.unbind();

  Terrain terrain;

  minorShader.bind();
  minorShader.sendUniformData("projection", perspectiveProjection);
  minorShader.sendUniformData("model", glm::mat4(1.0f));
  minorShader.unbind();

  Pyramid pyramid;
  pyramid.setPosition(glm::vec3(-0.5f, 0.0f, -3.0f));

  float startTime = gameClock.getTime();

  cb.setColors({Color::Red, Color::Green, Color::Blue, Color::Yellow,
                Color::Cyan, Color::Magenta});

  pyramid.setColors(
      {Color::Red, Color::Green, Color::Blue, Color::Yellow, Color::Cyan});

  while (!window->shouldClose()) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(Color::Black.r, Color::Black.g, Color::Black.b,
                 Color::Black.a);

    glm::mat4 viewMatrix = camera.getViewMatrix();

    float currentTime = gameClock.getTime();
    float deltaTime = currentTime - startTime;

    // terrain
    {
      minorShader.bind();
      minorShader.sendUniformData("view", viewMatrix);
      terrain.draw();
      minorShader.unbind();
    }

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

    // just call inputs if inputHandler not null
    if (inputHandler) {
      inputs();
    }

    window->swapBuffers();
    window->pollEvents();
  }
}

}  // namespace Brut