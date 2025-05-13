#include "BrutDesktopInputHandler.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Input/BrutInputHandler.hpp"

namespace Brut {

void keyCallback(GLFWwindow* window,
                 int key,
                 int scancode,
                 int action,
                 int mods) {
  DesktopInputHandler* handler =
      static_cast<DesktopInputHandler*>(glfwGetWindowUserPointer(window));

  int brutKey = BRUT_KEY_UNKNOWN;
  int brutAction = BRUT_KEY_ACTION_UNKNOWN;

  // if you know a better way, pls just do it
  // map glfw keys to brut keys
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
      brutKey = BRUT_KEY_ESCAPE;
      break;
    case GLFW_KEY_SPACE:
      brutKey = BRUT_KEY_SPACE;
      break;
    case GLFW_KEY_LEFT_CONTROL:
      brutKey = BRUT_KEY_LEFT_CTRL;
      break;
    case GLFW_KEY_RIGHT_CONTROL:
      brutKey = BRUT_KEY_RIGHT_CTRL;
      break;
    default:
      return;  // dont call callback if key not recognized
  };

  // same
  // map glfw actions to brut actions
  switch (action) {
    case GLFW_PRESS:
      brutAction = BRUT_KEY_ACTION_PRESS;
      break;
    case GLFW_RELEASE:
      brutAction = BRUT_KEY_ACTION_RELEASE;
      break;
    case GLFW_REPEAT:
      brutAction = BRUT_KEY_ACTION_REPEAT;
      break;
    default:
      return;  // dont call callback if action not recognized
  };

  handler->rawInputHandler->onKey(brutKey, brutAction);
}

void mouseCallback(GLFWwindow* window, double xPos, double yPos) {
  DesktopInputHandler* handler =
      static_cast<DesktopInputHandler*>(glfwGetWindowUserPointer(window));

  glm::vec2 pos{static_cast<float>(xPos), static_cast<float>(yPos)};

  handler->rawInputHandler->onMouse(pos);
}

DesktopInputHandler::DesktopInputHandler(GLFWwindow* _glfwWindow,
                                         InputHandler* _rawInputHandler)
    : glfwWindow(_glfwWindow), rawInputHandler(_rawInputHandler) {
  glfwSetWindowUserPointer(glfwWindow, this);
  glfwSetKeyCallback(glfwWindow, keyCallback);
  glfwSetCursorPosCallback(glfwWindow, mouseCallback);
}

}  // namespace Brut