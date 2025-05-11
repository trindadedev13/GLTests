#include "BrutGame.hpp"

#include <iostream>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Graphics/BrutColor.hpp"
#include "Graphics/Shader/BrutShader.hpp"
#include "Objects/BrutCube.hpp"
#include "Objects/BrutTerrain.hpp"
#include "config.h"

namespace Brut {

Game::Game() {
  gladLoadGL(glfwGetProcAddress);
  glEnable(GL_DEPTH_TEST);
}

Game::~Game() {}

void Game::run() {
  float aspectRatio = static_cast<float>(GL_WINDOW_WIDTH) / GL_WINDOW_HEIGHT;

  glm::mat4 projection =
      glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 10.0f);

  Shader cubeShader = shadersManager.get("cube");
  Shader terrainShader = shadersManager.get("terrain");

  Cube cb;
  cb.setPosition(0.0f, 0.0f, -5.0f);

  cubeShader.bind();
  cubeShader.sendUniformData("projection", projection);
  cubeShader.unbind();

  Terrain terrain;

  terrainShader.bind();
  terrainShader.sendUniformData("projection", projection);
  terrainShader.sendUniformData("model", glm::mat4(1.0f));
  terrainShader.unbind();

  float startTime = glfwGetTime();

  cb.setColors({Color::Red, Color::Green, Color::Blue, Color::Yellow,
                Color::Cyan, Color::Magenta});

  while (!window.shouldClose()) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(Color::Black.r, Color::Black.g, Color::Black.b,
                 Color::Black.a);

    float currentTime = glfwGetTime();
    float deltaTime = currentTime - startTime;

    glm::mat4 cubeModel = glm::mat4(1.0f);
    cubeModel = glm::rotate(cubeModel, -deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
    cubeModel =
        glm::rotate(cubeModel, 1.75f * deltaTime, glm::vec3(1.f, 0.f, 0.f));
    cubeModel =
        glm::rotate(cubeModel, 0.75f * deltaTime, glm::vec3(0.f, 0.f, 1.f));
    cubeModel = glm::scale(cubeModel, glm::vec3(.5f, .5f, .5f));

    glm::mat4 cubeModelToWorld = cb.getPosition() * cubeModel;

    {
      cubeShader.bind();
      cubeShader.sendUniformData("model", cubeModelToWorld);
      cb.draw();
      cubeShader.unbind();
    }

    {
      terrainShader.bind();
      terrain.draw();
      terrainShader.unbind();
    }

    window.swapBuffers();
    glfwPollEvents();
  }
}

}  // namespace Brut