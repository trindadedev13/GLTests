#include "BrutDesktopInputHandler.hpp"

#include <GLFW/glfw3.h>

#include "Input/BrutInputHandler.hpp"

namespace Brut {

void keyCallback(GLFWwindow* window,
                 int key,
                 int scancode,
                 int action,
                 int mods) {
  // map glfw keys/actions to brut because of multplatform
  DesktopInputHandler* handler =
      static_cast<DesktopInputHandler*>(glfwGetWindowUserPointer(window));

  int brutKey = -1;
  int brutAction = -1;

  switch (key) {
    case GLFW_KEY_W:
      brutKey = BRUT_KEY_W;
      break;
    case GLFW_KEY_A:
      brutKey = BRUT_KEY_A;
      break;
    case GLFW_KEY_S:
      brutKey = BRUT_KEY_S;
      break;
    case GLFW_KEY_D:
      brutKey = BRUT_KEY_D;
      break;
    case GLFW_KEY_ESCAPE:
      brutKey = BRUT_KEY_ESC;
      break;
    case GLFW_KEY_SPACE:
      brutKey = BRUT_KEY_SPC;
      break;
    default:
      return;  // Ignorar teclas não mapeadas
  }

  switch (action) {
    case GLFW_PRESS:
      brutAction = BRUT_KEY_ACTION_PRESS;
      break;
    case GLFW_REPEAT:
      brutAction = BRUT_KEY_ACTION_REPEAT;
      break;
    case GLFW_RELEASE:
      brutAction = BRUT_KEY_ACTION_RELEASE;
      break;
    default:
      return;  // ignore actions that idc
  }

  handler->rawInputHandler->onKey(brutKey, brutAction);
}

DesktopInputHandler::DesktopInputHandler(GLFWwindow* _glfwWindow,
                                         InputHandler* _rawInputHandler)
    : glfwWindow(_glfwWindow), rawInputHandler(_rawInputHandler) {
  glfwSetWindowUserPointer(glfwWindow, this);
  glfwSetKeyCallback(glfwWindow, keyCallback);
}

}  // namespace Brut