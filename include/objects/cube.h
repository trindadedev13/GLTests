#ifndef CUBE_H
#define CUBE_H

#include <cglm/cglm.h>
#include "graphics/color.h"

struct cube {
  GLuint cube_vao;  // vertex array object
  GLuint cube_vbo;  // vertex buffer object
  GLuint cube_shader_program;
  GLfloat* mvp_matrix;
  mat4 cube_model_matrix;
  color cube_color;
};

struct cube* cube_create();

void cube_draw(struct cube*);

#endif