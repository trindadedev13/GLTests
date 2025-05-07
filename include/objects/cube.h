#ifndef CUBE_H
#define CUBE_H

#include <cglm/cglm.h>
#include <glad/gl.h>

#include "graphics/color.h"

struct cube {
  GLuint cube_vao;  // vertex array object
  GLuint cube_vbo;  // vertex buffer object
  GLuint cube_shader_program;
  mat4 cube_model_matrix;
  color cube_color;
  mat4 matrix_mvp;
};

struct cube* cube_create();

void cube_draw(struct cube*);

void cube_reset_model_matrix(struct cube*);

#endif