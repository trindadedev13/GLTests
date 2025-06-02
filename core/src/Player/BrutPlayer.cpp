#include "Player/BrutPlayer.hpp"

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

#include "Player/BrutInventory.hpp"

namespace Brut {

Player::Player()
    : inventory{},
      position{0.0f, 0.0f, 0.0f},
      viewDirection{glm::vec3{0.0f, 0.0f, -1.0f}},
      left{glm::vec3{-1.0f, 0.0f, 0.0f}},
      sensitivity{250.0f},
      pitchAngle{0.0f} {}

Player::~Player() {}

void Player::setMagnitude(glm::vec2& pos, float val) {
  glm::vec2 vec = glm::normalize(pos);
  pos = val * vec;
}

void Player::setPosition(const glm::vec3& nPosition) {
  position = nPosition;
}

void Player::moveForward() {
  position = position + viewDirection * speed;
}

void Player::moveBack() {
  position = position + viewDirection * (-speed);
}

void Player::moveRight() {
  position = position + left * (-speed);
}

void Player::moveLeft() {
  position = position + left * speed;
}

void Player::jump() {
  if (!isJumping) {
    velocityY = jumpStrength;
    jumpOldY = position.y;
    isJumping = true;
  }
}

void Player::update() {
  if (isJumping) {
    velocityY += gravity;
    position.y += velocityY;

    if (position.y <= jumpOldY) {
      position.y = jumpOldY;
      velocityY = 0.0f;
      isJumping = false;
    }
  }
}

void Player::mouseUpdate(const glm::vec2& nPosition) {
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
  float pitchChange = delta.y;
  float newPitch = pitchAngle + pitchChange;

  if (newPitch > -89.0f && newPitch < 89.0f) {
    glm::mat4 pitchMatrix = glm::rotate(glm::radians(delta.y), left);
    viewDirection = glm::mat3(pitchMatrix) * viewDirection;
    viewDirection = glm::normalize(viewDirection);
    pitchAngle = newPitch;
  }
}

const glm::vec3& Player::getPosition() const {
  return position;
}

const glm::vec3& Player::getViewDirection() const {
  return viewDirection;
}

const glm::vec3& Player::getLeft() const {
  return left;
}

}  // namespace Brut
