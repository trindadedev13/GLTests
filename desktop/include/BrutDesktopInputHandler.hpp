#include <GLFW/glfw3.h>

#include "Input/BrutInputHandler.hpp"

namespace Brut {

class DesktopInputHandler {
 public:
  DesktopInputHandler(GLFWwindow* glfwWindow, InputHandler* rawInputHandler);

  InputHandler* rawInputHandler;

 private:
  GLFWwindow* glfwWindow;
};

}  // namespace Brut