#ifndef BRUT_SDL_WINDOW_HPP
#define BRUT_SDL_WINDOW_HPP

#include <string>

#include <glad/glad.h>
#include <SDL3/SDL.h>

#include "Window/BrutIWindow.hpp"

namespace Brut {

class SDLWindow : public IWindow {
 public:
  SDLWindow(int w, int h, std::string name);
  ~SDLWindow();

  SDLWindow(const SDLWindow&) = delete;
  SDLWindow& operator=(const SDLWindow&) = delete;

  bool isRunning() override;

  void swapBuffers() override;

  void close() override;

 private:
  SDL_Window* sdlWindow;
  SDL_GLContext glContext;
  bool running{true};

  void initWindow();
};

}  // namespace Brut

#endif