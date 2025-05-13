#include "Camera/BrutCamera.hpp"

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

namespace Brut {

Camera::Camera(float _windowWidth, float _windowHeight)
    : position{glm::vec3{0.0f}},
      viewDirection{glm::vec3{0.0f, 0.0f, -1.0f}},
      left{glm::vec3{-1.0f, 0.0f, 0.0f}},
      UP{glm::vec3{0.0f, 1.0f, 0.0f}},
      SPEED_MAG{0.45f},
      mouseOldPosition{glm::vec2{0.0f}},
      mouseIsEnable{false},
      sensitivity{50.0f},
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

void Camera::mouseUpdate(const glm::vec2& nPosition) {
  if (!mouseIsEnable) {
    mouseOldPosition = nPosition;
    mouseIsEnable = true;
  }

  glm::vec2 delta = nPosition - mouseOldPosition;
  float threshold = sensitivity / 100.0f;
  if (glm::length(delta) > threshold) {
    setMagnitude(delta, threshold);
  }

  mouseOldPosition = nPosition;

  // horizontal rotation (around the global Y axis - "UP")
  glm::mat4 yawMatrix = glm::rotate(glm::radians(-delta.x), glm::vec3(UP));
  viewDirection = glm::mat3(yawMatrix) * viewDirection;

  // updates "left" axis after yaw
  left = glm::normalize(glm::cross(UP, viewDirection));

  // vertical rotation (around the "left" axis )
  glm::mat4 pitchMatrix = glm::rotate(glm::radians(delta.y), left);
  viewDirection = glm::mat3(pitchMatrix) * viewDirection;

  viewDirection = glm::normalize(viewDirection);
}

void Camera::setMagnitude(glm::vec2& pos, float val) {
  glm::vec2 vec = glm::normalize(pos);
  pos = val * vec;
}

void Camera::setSensitivity(const float nSensitivity) {
  sensitivity = nSensitivity;
}

glm::mat4 Camera::getViewMatrix() const {
  return glm::lookAt(position, position + viewDirection, UP);
}

glm::mat4 Camera::getPerspectiveProjectionMatrix() const {
  return perspectiveProjection;
}

}  // namespace Brut