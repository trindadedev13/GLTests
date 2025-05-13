#include "Input/BrutInputHandler.hpp"

#include <functional>

#include <glm/glm.hpp>

namespace Brut {

void InputHandler::setOnKeyCallback(KeyCallback callback) {
  onKeyCallback = callback;
}

void InputHandler::setOnMouseCallback(MouseCallback callback) {
  onMouseCallback = callback;
}

void InputHandler::onKey(int key, int action) {
  if (onKeyCallback)
    onKeyCallback(key, action);
}

void InputHandler::onMouse(const glm::vec2 position) {
  if (onMouseCallback)
    onMouseCallback(position);
}

}  // namespace Brut