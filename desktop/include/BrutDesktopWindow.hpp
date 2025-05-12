#ifndef BRUT_DESKTOP_WINDOW_HPP
#define BRUT_DESKTOP_WINDOW_HPP

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "BrutIWindow.hpp"

namespace Brut {

class DesktopWindow : public IWindow {
 public:
  DesktopWindow(int w, int h, std::string name);
  ~DesktopWindow();

  DesktopWindow(const DesktopWindow&) = delete;
  DesktopWindow& operator=(const DesktopWindow&) = delete;

  GLFWwindow* glfwWindow;

  bool shouldClose() override;

  void swapBuffers() override;

  void pollEvents() override;

  void close() override;

 private:
  void initWindow();
  void configureWindowPosition();
};

}  // namespace Brut

#endif