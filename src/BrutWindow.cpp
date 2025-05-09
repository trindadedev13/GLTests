#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "BrutWindow.hpp"

namespace Brut {

Window::Window(int w, int h, std::string name)
    : width(w), height(h), windowName(name) {
  initWindow();
}

Window::~Window() {
  glfwDestroyWindow(window);
  glfwTerminate();
}

void Window::initWindow() {
  glfwInit();

  window =
      glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);

  glfwMakeContextCurrent(window);
}

}  // namespace Brut