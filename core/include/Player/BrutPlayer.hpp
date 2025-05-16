#ifndef BRUT_PLAYER_HPP
#define BRUT_PLAYER_HPP

#include <glm/glm.hpp>

#include "Player/BrutInventory.hpp"

namespace Brut {

class Player {
 public:
  Player();
  ~Player();

  const float speed;

  Inventory inventory;

  void setPosition(const glm::vec3& nPos);
  void moveForward();
  void moveBack();
  void moveLeft();
  void moveRight();

  void setSensitivity(float nSensitivity);
  void mouseUpdate(const glm::vec2& nPos);

  const glm::vec3& getPosition() const;
  const glm::vec3& getViewDirection() const;
  const glm::vec3& getLeft() const;

 private:
  glm::vec3 position;
  glm::vec3 viewDirection;
  glm::vec3 left;
  glm::vec2 mouseOldPosition;
  bool mouseIsEnable;
  float sensitivity;
  float pitchAngle;
  const glm::vec3 UP{0.0f, 1.0f, 0.0f};

  void setMagnitude(glm::vec2& pos, float val);
};

}  // namespace Brut

#endif