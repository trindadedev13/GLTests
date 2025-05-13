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
  gladLoadGL();  // loads glad AFTER create opengl context
}

DesktopWindow::~DesktopWindow() {
  glfwDestroyWindow(glfwWindow);
  glfwTerminate();
}

void DesktopWindow::initWindow() {
  glfwInit();

  GLFWmonitor* monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode* mode = glfwGetVideoMode(monitor);
  width = mode->width;
  height = mode->height;

  glfwWindow =
      glfwCreateWindow(width, height, windowName.c_str(), monitor, nullptr);

  glfwMakeContextCurrent(glfwWindow);  // creates open gl context
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

void DesktopWindow::close() {
  glfwSetWindowShouldClose(glfwWindow, GL_TRUE);
}

}  // namespace Brut