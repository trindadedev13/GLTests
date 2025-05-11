#ifndef BRUT_ANDROID_WINDOW_HPP
#define BRUT_ANDROID_WINDOW_HPP

#include <SDL3/SDL.h>
#include <string>

#include "BrutIWindow.hpp"

namespace Brut {

class AndroidWindow : public IWindow {
 public:
  AndroidWindow(int w, int h, std::string name);
  ~AndroidWindow() override;

  AndroidWindow(const AndroidWindow&) = delete;
  AndroidWindow& operator=(const AndroidWindow&) = delete;

  bool shouldClose() override;
  void swapBuffers() override;
  void pollEvents() override;

 private:
  void initWindow();

  SDL_Window* sdlWindow = nullptr;
  SDL_GLContext glContext = nullptr;
  bool closed = false;
};

}  // namespace Brut

#endif