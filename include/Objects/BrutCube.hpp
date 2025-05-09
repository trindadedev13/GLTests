#ifndef BRUT_CUBE_HPP
#define BRUT_CUBE_HPP

#include <glm/glm.hpp>

namespace Brut {

class Cube {
 public:
  Cube();
  ~Cube();

  void setPosition(float x, float y, float z);

  glm::mat4 getPosition() const;

  void draw();

 private:
  unsigned int VAO;
  unsigned int EBO;
  unsigned int positionVBO;
  unsigned int colorVBO;

  glm::vec3 position;
  glm::mat4 model;

  void initCube();
  void createBuffers();
  void fillBuffers();
  void linkBuffers();

  void updatePosition();
};

}  // namespace Brut

#endif