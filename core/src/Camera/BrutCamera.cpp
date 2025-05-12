#include "Camera/BrutCamera.hpp"

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

namespace Brut {

Camera::Camera()
    : position(glm::vec3(0.0f)),
      viewDirection(glm::vec3(0.0f, 0.0f, -1.0f)),
      left(glm::vec3(-1.0f, 0.0f, 0.0f)),
      UP(glm::vec3(0.0f, 1.0f, 0.0f)),
      SPEED_MAG(0.05f) {}

Camera::~Camera() {}

glm::mat4 Camera::enable() {
  return glm::lookAt(position, position + viewDirection, UP);
}

void Camera::moveForward() {
  position = position + viewDirection * SPEED_MAG;
}

void Camera::moveBack() {
  position = position + viewDirection * (-SPEED_MAG);
}

void Camera::moveRight() {
  position = position + left * (-SPEED_MAG);
}

void Camera::moveLeft() {
  position = position + left * SPEED_MAG;
}

}  // namespace Brut