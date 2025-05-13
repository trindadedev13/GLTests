#ifndef BRUT_CAMERA_HPP
#define BRUT_CAMERA_HPP

#include <glm/glm.hpp>

namespace Brut {

class Camera {
 public:
  Camera(float windowWidth, float windowHeight);
  ~Camera();

  void moveForward();
  void moveBack();
  void moveLeft();
  void moveRight();

  void mouseUpdate(const glm::vec2& nPosition);

  void setSensitivity(const float nSensitivity);

  glm::mat4 getViewMatrix() const;
  glm::mat4 getPerspectiveProjectionMatrix() const;

 private:
  glm::vec3 position;
  glm::vec3 viewDirection;
  glm::vec3 left;
  glm::mat4 perspectiveProjection;

  /** window width & height */
  float windowWidth;
  float windowHeight;

  /** The fov of camera */
  float fov;
  /** The render distance, aka ZFar */
  float renderDistance;
  /** The sensivity of camera mouse move */
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