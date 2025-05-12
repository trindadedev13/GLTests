#ifndef BRUT_OBJECT_HPP
#define BRUT_OBJECT_HPP

#include <glm/glm.hpp>

#include "Buffer/BrutBuffer.hpp"
#include "Buffer/BrutVertexArrayBuffer.hpp"

namespace Brut {

class Object {
 public:
  Object();
  virtual ~Object();
  virtual void draw() = 0;

  /** Defines the position variable with nPosition value. */
  void setPosition(const glm::vec3 nPosition);

  /** Returns the model with position. */
  glm::mat4 getPosition() const;

 protected:
  /** Buffers */
  VertexArrayBuffer VAO;
  ArrayBuffer verticesVBO;
  ArrayBuffer colorVBO;
  ElementArrayBuffer EBO;

  /** Stores the object position. */
  glm::vec3 position;
  /** The matrix with position */
  glm::mat4 model;

  void updatePosition();
};

}  // namespace Brut

#endif