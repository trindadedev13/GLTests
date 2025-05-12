#include "Objects/Primitives/BrutObject.hpp"

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

namespace Brut {

Object::Object()
    : VAO{}, EBO{}, verticesVBO{}, colorVBO{}, position{0.f}, model{1.f} {}

Object::~Object() {}

void Object::setPosition(const glm::vec3 nPosition) {
  position = nPosition;
  updatePosition();
}

glm::mat4 Object::getPosition() const {
  return model;
}

void Object::updatePosition() {
  model = glm::translate(position);
}

}  // namespace Brut