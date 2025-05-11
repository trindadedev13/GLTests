#include "BrutDesktopWindow.hpp"

#include <string>
#include <utility>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "BrutIWindow.hpp"

namespace Brut {

DesktopWindow::DesktopWindow(int w, int h, std::string name)
    : IWindow(w, h, std::move(name)) {
  initWindow();
  configureWindowPosition();
  gladLoadGL();  // loads glad AFTER create opengl context
}

DesktopWindow::~DesktopWindow() {
  glfwDestroyWindow(glfwWindow);
  glfwTerminate();
}

void DesktopWindow::initWindow() {
  glfwInit();

  glfwWindow =
      glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);

  glfwMakeContextCurrent(glfwWindow);  // creates open gl context
}

void DesktopWindow::configureWindowPosition() {
  GLFWmonitor* monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode* mode = glfwGetVideoMode(monitor);

  int xPos = (mode->width - width) / 2;
  int yPos = (mode->height - height) / 2;

  glfwSetWindowPos(glfwWindow, xPos, yPos);
}

bool DesktopWindow::shouldClose() {
  return glfwWindowShouldClose(glfwWindow);
}

void DesktopWindow::swapBuffers() {
  glfwSwapBuffers(glfwWindow);
}

void DesktopWindow::pollEvents() {
  glfwPollEvents();
}

}  // namespace Brut