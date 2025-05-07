#include "renderer.h"

#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "config.h"

int glrenderer_init_window(struct glrenderer* renderer) {
  renderer->window = glfwCreateWindow(GL_WINDOW_WIDTH, GL_WINDOW_HEIGHT,
                                      GL_WINDOW_NAME, NULL, NULL);
  if (!renderer->window) {
    glfwTerminate();
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

void glrenderer_configure_window(struct glrenderer* renderer) {
  GLFWmonitor* monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode* mode = glfwGetVideoMode(monitor);

  int xpos = (mode->width - GL_WINDOW_WIDTH) / 2;
  int ypos = (mode->height - GL_WINDOW_HEIGHT) / 2;

  glfwSetWindowPos(renderer->window, xpos, ypos);

  glfwMakeContextCurrent(renderer->window);

  glEnable(GL_DEPTH_TEST);
}

void glrenderer_end(struct glrenderer* renderer) {
  glfwDestroyWindow(renderer->window);
  glfwTerminate();
}

void glrenderer_swap_buffers(struct glrenderer* renderer) {
  glfwSwapBuffers(renderer->window);
}