#ifndef BRUT_IWINDOW_HPP
#define BRUT_IWINDOW_HPP

#include <string>

namespace Brut {

// Abstract class for game window
// REMEMBER: When implementing this, be sure to initialize Glad and OpenGL
// Context!
class IWindow {
 public:
  IWindow(int w, int h, std::string name);
  virtual ~IWindow() = default;

  /** return if window is open/running. */
  virtual bool isRunning() = 0;

  /** swap back and front buffers. */
  virtual void swapBuffers() = 0;

  /** closes the window */
  virtual void close() = 0;

  int width;
  int height;
  const std::string windowName;
};

}  // namespace Brut

#endif