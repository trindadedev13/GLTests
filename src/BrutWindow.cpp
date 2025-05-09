#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "BrutWindow.hpp"

namespace Brut {

Window::Window(int w, int h, std::string name)
    : width{w}, height{h}, windowName{name} {
  initWindow();
  configureWindowPosition();
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

void Window::configureWindowPosition() {
  GLFWmonitor* monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode* mode = glfwGetVideoMode(monitor);

  int xPos = (mode->width  - width) / 2;
  int yPos = (mode->height - height) / 2;

  glfwSetWindowPos(window, xPos, yPos);
}

}  // namespace Brut