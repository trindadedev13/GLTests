#ifndef RENDERER_H
#define RENDERER_H

#include <GLFW/glfw3.h>

struct glrenderer {
  GLFWwindow* window;
};

int glrenderer_init_window(struct glrenderer*);

void glrenderer_configure_window(struct glrenderer*);

void glrenderer_end(struct glrenderer*);

void glrenderer_swap_buffers(struct glrenderer*);

#endif