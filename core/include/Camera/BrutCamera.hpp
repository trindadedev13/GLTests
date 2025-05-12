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

 private:
  glm::vec3 position;
  glm::vec3 viewDirection;
  glm::vec3 left;

  const glm::vec3 UP;
  const float SPEED_MAG;
};

}  // namespace Brut

#endif