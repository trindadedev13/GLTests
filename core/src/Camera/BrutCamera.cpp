#include "Camera/BrutCamera.hpp"

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

namespace Brut {

Camera::Camera(float _windowWidth, float _windowHeight)
    : position{glm::vec3{0.0f}},
      viewDirection{glm::vec3{0.0f, 0.0f, -1.0f}},
      UP{glm::vec3{0.0f, 1.0f, 0.0f}},
      perspectiveProjection{1.0f},
      fov{55.0f},
      renderDistance{100.0f},
      windowWidth{_windowWidth},
      windowHeight{_windowHeight} {
  float aspectRatio = windowWidth / windowHeight;
  perspectiveProjection =
      glm::perspective(glm::radians(fov), aspectRatio, 0.1f, renderDistance);
}

Camera::~Camera() {}

void Camera::followPlayer(const Player& player) {
  position = player.getPosition();
  viewDirection = player.getViewDirection();
}

glm::mat4 Camera::getViewMatrix() const {
  return glm::lookAt(position, position + viewDirection, UP);
}

glm::mat4 Camera::getPerspectiveProjectionMatrix() const {
  return perspectiveProjection;
}

}  // namespace Brut