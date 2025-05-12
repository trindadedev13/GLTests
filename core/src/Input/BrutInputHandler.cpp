#include "Input/BrutInputHandler.hpp"

#include <functional>

namespace Brut {

void InputHandler::setOnKeyCallback(KeyCallback callback) {
  onKeyCallback = callback;
}

void InputHandler::onKey(int key, int action) {
  if (onKeyCallback)
    onKeyCallback(key, action);
}

}  // namespace Brut