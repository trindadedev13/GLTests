#ifndef CUBE_H
#define CUBE_H

#include "graphics/color.h"

struct cube {
  GLuint cube_vao;
  GLuint cube_vbo;
  GLuint cube_shader_program;
  GLfloat* mvp_matrix;
  color cube_color;
};

struct cube* cube_create();

void cube_draw(struct cube*);

#endif