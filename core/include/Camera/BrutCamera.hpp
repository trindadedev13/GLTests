#ifndef BRUT_CAMERA_HPP
#define BRUT_CAMERA_HPP

#include <glm/glm.hpp>

namespace Brut {

class Camera {
 public:
  Camera();
  ~Camera();

  glm::mat4 enable();
  void moveForward();
  void moveBack();
  void moveLeft();
  void moveRight();

  void mouseUpdate(const glm::vec2& nPosition);

  void setSensitivity(const float nSensitivity);

 private:
  glm::vec3 position;
  glm::vec3 viewDirection;
  glm::vec3 left;
  float sensitivity;

  const glm::vec3 UP;
  const float SPEED_MAG;

  // mouse
  glm::vec2 mouseOldPosition;
  bool mouseIsEnable;
  void setMagnitude(glm::vec2& pos, float val);
};

}  // namespace Brut

#endif