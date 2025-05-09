#include <iostream>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "BrutGame.hpp"
#include "Graphics/BrutColor.hpp"
#include "Graphics/BrutShader.hpp"
#include "Objects/BrutCube.hpp"
#include "config.h"

namespace Brut {

Game::Game() {
  gladLoadGL(glfwGetProcAddress);
  glEnable(GL_DEPTH_TEST);
}

Game::~Game() {}

void Game::run() {
  glm::mat4 projection =
      glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 10.0f);

  std::string vertFP =
      std::string(BRUT_RUNNING_PATH) + "/shaders/cube/cube.vert";
  std::string fragFP =
      std::string(BRUT_RUNNING_PATH) + "/shaders/cube/cube.frag";

  Shader cubeShader(vertFP, fragFP);

  Cube cb;
  cb.setPosition(0.0f, 0.0f, -5.0f);

  cubeShader.bind();
  cubeShader.sendUniformData("projection", projection);

  float startTime = glfwGetTime();

  std::cout << sizeof(cb.faceColors) << std::endl;

  cb.setColors({Color::Red, Color::Green, Color::Blue, Color::Yellow,
                Color::Cyan, Color::Magenta});

  while (!window.shouldClose()) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(Color::White.r, Color::White.g, Color::White.b,
                 Color::White.a);

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
    cubeShader.sendUniformData("model", cubeModelToWorld);
    cb.draw();

    window.swapBuffers();
    glfwPollEvents();
  }
}

}  // namespace Brut