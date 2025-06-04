#ifndef BRUT_PLAYER_HPP
#define BRUT_PLAYER_HPP

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "Player/BrutInventory.hpp"

namespace Brut {

class Player {
 public:
  Player();
  ~Player();

  Inventory inventory;

  // setters
  void setPosition(const glm::vec3& nPos);
  void setSensitivity(float nSensitivity);

  // move
  void moveForward();
  void moveBack();
  void moveLeft();
  void moveRight();
  void jump();

  // updates, call it on game loop
  void update();

  // mouse
  void mouseUpdate(const glm::vec2& nPos);

  // getters
  const glm::vec3& getPosition() const;
  const glm::vec3& getViewDirection() const;
  const glm::vec3& getLeft() const;

 private:
  const float speed{0.45f};
  const float gravity{-0.1f};
  const float jumpStrength{1.0f};

  const glm::vec3 UP{0.0f, 1.0f, 0.0f};

  glm::vec3 position;
  glm::vec3 viewDirection;
  glm::vec3 left;
  glm::vec2 mouseOldPosition;

  bool mouseIsEnable;
  bool isJumping{false};

  float jumpOldY{0.0f};

  float sensitivity;
  float pitchAngle;
  float velocityY{0.0f};

  void setMagnitude(glm::vec2& pos, float val);
};

}  // namespace Brut

#endif