#include "BrutGame.hpp"

#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "BrutConfig.hpp"
#include "BrutIWindow.hpp"
#include "Graphics/BrutColor.hpp"
#include "Graphics/Shader/BrutShader.hpp"
#include "Objects/Primitives/BrutCube.hpp"
#include "Objects/Primitives/BrutPyramid.hpp"
#include "Objects/Primitives/BrutTerrain.hpp"

namespace Brut {

Game::Game(IWindow* _window) : window(_window) {
  glEnable(GL_DEPTH_TEST);
}

Game::~Game() {}

void Game::run() {
  float aspectRatio = static_cast<float>(window->width) / window->height;

  glm::mat4 projection =
      glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 15.0f);

  Shader defShader = shadersManager.get("defShader");
  Shader minorShader = shadersManager.get("minorShader");

  Cube cb;
  cb.setPosition(glm::vec3(1.0f, 0.0f, -5.0f));

  defShader.bind();
  defShader.sendUniformData("projection", projection);
  defShader.unbind();

  Terrain terrain;

  minorShader.bind();
  minorShader.sendUniformData("projection", projection);
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

    float currentTime = gameClock.getTime();
    float deltaTime = currentTime - startTime;

    glm::mat4 cubeModel = glm::mat4(1.0f);
    cubeModel = glm::rotate(cubeModel, -deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
    cubeModel =
        glm::rotate(cubeModel, 1.75f * deltaTime, glm::vec3(1.f, 0.f, 0.f));
    cubeModel =
        glm::rotate(cubeModel, 0.75f * deltaTime, glm::vec3(0.f, 0.f, 1.f));
    cubeModel = glm::scale(cubeModel, glm::vec3(.5f, .5f, .5f));

    {
      glm::mat4 cubeModelToWorld = cb.getPosition() * cubeModel;
      defShader.bind();
      defShader.sendUniformData("model", cubeModelToWorld);
      cb.draw();
      defShader.unbind();
    }

    {
      glm::mat4 pyramidModelToWorld = pyramid.getPosition() * cubeModel;
      defShader.bind();
      defShader.sendUniformData("model", pyramidModelToWorld);
      pyramid.draw();
      defShader.unbind();
    }

    {
      minorShader.bind();
      terrain.draw();
      minorShader.unbind();
    }

    window->swapBuffers();
    window->pollEvents();
  }
}

}  // namespace Brut