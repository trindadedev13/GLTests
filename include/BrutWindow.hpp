#ifndef BRUT_WINDOW_HPP
#define BRUT_WINDOW_HPP

#include <GLFW/glfw3.h>
#include <string>

namespace Brut {

class Window {
 public:
  Window(int w, int h, std::string name);
  ~Window();

  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;

  /* checks if user closed window or whatever */
  bool shouldClose() { return glfwWindowShouldClose(window); }

  /* swap back and front buffers */
  void swapBuffers() { glfwSwapBuffers(window); }

 private:
  void initWindow();
  void configureWindowPosition();

  const int width;
  const int height;
  const std::string windowName;

  GLFWwindow* window;
};

}  // namespace Brut

#endif