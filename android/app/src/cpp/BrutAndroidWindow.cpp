#include "BrutAndroidWindow.hpp"

#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <utility>

namespace Brut {

AndroidWindow::AndroidWindow(int w, int h, std::string name)
    : IWindow(w, h, std::move(name)) {
  initWindow();
}

AndroidWindow::~AndroidWindow() {
  if (glContext) SDL_GL_DeleteContext(glContext);
  if (sdlWindow) SDL_DestroyWindow(sdlWindow);
  SDL_Quit();
}

void AndroidWindow::initWindow() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Failed to init SDL: %s", SDL_GetError());
    closed = true;
    return;
  }

  // Configure SDL for OpenGL ES
  SDL_SetHint(SDL_HINT_ORIENTATIONS, "LandscapeLeft LandscapeRight");

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

  sdlWindow = SDL_CreateWindow(windowName.c_str(), width, height, SDL_WINDOW_OPENGL);
  if (!sdlWindow) {
    SDL_Log("Failed to create SDL window: %s", SDL_GetError());
    closed = true;
    return;
  }

  glContext = SDL_GL_CreateContext(sdlWindow);
  if (!glContext) {
    SDL_Log("Failed to create OpenGL context: %s", SDL_GetError());
    closed = true;
    return;
  }

  SDL_GL_MakeCurrent(sdlWindow, glContext);

  SDL_GetWindowSizeInPixels(sdlWindow, &width, &height);

  gladLoadGLES2Loader((GLADloadproc) SDL_GL_GetProcAddress);
}

bool AndroidWindow::shouldClose() {
  return closed;
}

void AndroidWindow::swapBuffers() {
  SDL_GL_SwapWindow(sdlWindow);
}

void AndroidWindow::pollEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) {
      closed = true;
    }
  }
}

}  // namespace Brut