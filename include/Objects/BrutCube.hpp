#ifndef BRUT_CUBE_HPP
#define BRUT_CUBE_HPP

#include "Buffer/BrutBuffer.hpp"
#include "Graphics/BrutColor.hpp"

#include <array>
#include <glm/glm.hpp>

namespace Brut {

class Cube {
 public:
  Cube();
  ~Cube();

  std::array<Color, 6> faceColors = {Color::White, Color::White, Color::White,
                                     Color::White, Color::White, Color::White};

  void setPosition(float x, float y, float z);
  void setColors(const std::array<Color, 6>& newFaceColors);

  glm::mat4 getPosition() const;

  void draw();

 private:
  unsigned int VAO;
  // unsigned int EBO;
  // unsigned int positionVBO;
  // unsigned int colorVBO;

  ArrayBuffer positionVBO;
  ArrayBuffer colorVBO;
  ElementArrayBuffer EBO;

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