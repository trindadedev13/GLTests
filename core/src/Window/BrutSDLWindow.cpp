#include "Window/BrutSDLWindow.hpp"

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <SDL3/SDL.h>

#include "Error/BrutError.hpp"
#include "Window/BrutIWindow.hpp"

namespace Brut {

SDLWindow::SDLWindow(int w, int h, std::string name)
    : IWindow(w, h, std::move(name)) {
  initWindow();
}

SDLWindow::~SDLWindow() {
  SDL_GL_DestroyContext(glContext);
  SDL_DestroyWindow(sdlWindow);
  SDL_Quit();
}

void SDLWindow::initWindow() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    fatalError("Failed to initialize SDL Video : " +
               std::string(SDL_GetError()));
  }

// configures gl
#ifdef BRUT_USE_OPENGL_ES
  // OpenGL ES 3.2
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#else
  // OpenGL 4.5
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif

  // create window
  sdlWindow = SDL_CreateWindow(windowName.c_str(), width, height,
                               SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  if (!sdlWindow) {
    fatalError("Failed to create SDL Window : " + std::string(SDL_GetError()));
  }

  // create glcontext
  glContext = SDL_GL_CreateContext(sdlWindow);
  if (!glContext) {
    fatalError("Failed to create OpenGL Context : " +
               std::string(SDL_GetError()));
  }

// init glad
#ifdef BRUT_USE_OPENGL_ES
  if (!gladLoadGLES2Loader((GLADloadproc)SDL_GL_GetProcAddress)) {
    fatalError("Failed to initialze GLAD Open GL ES 2");
  }
#else
  if (!gladLoadGL()) {
    fatalError("Failed to initialize GLAD Open GL");
  }
#endif

  std::cout << "Open GL Version : " << glGetString(GL_VERSION) << std::endl;
}

bool SDLWindow::isRunning() {
  return running;
}

void SDLWindow::swapBuffers() {
  SDL_GL_SwapWindow(sdlWindow);
}

void SDLWindow::close() {
  running = false;
}

}  // namespace Brut