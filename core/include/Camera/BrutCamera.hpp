#ifndef BRUT_CAMERA_HPP
#define BRUT_CAMERA_HPP

#include <glm/glm.hpp>

#include "Player/BrutPlayer.hpp"

namespace Brut {

class Camera {
 public:
  Camera(float windowWidth, float windowHeight);
  ~Camera();

  void followPlayer(const Player& player);

  glm::mat4 getViewMatrix() const;
  glm::mat4 getPerspectiveProjectionMatrix() const;

 private:
  glm::vec3 position;
  glm::vec3 viewDirection;
  glm::mat4 perspectiveProjection;

  /** window width & height */
  float windowWidth;
  float windowHeight;

  /** The fov of camera */
  float fov;
  /** The render distance, aka ZFar */
  float renderDistance;

  const glm::vec3 UP;
};

}  // namespace Brut

#endif