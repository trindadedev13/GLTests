#ifndef CUBE_H
#define CUBE_H

#include <cglm/cglm.h>
#include <glad/gl.h>

#include "graphics/color.h"

#define cube_reset_model_matrix(cube) \
  glm_mat4_identity((cube).cube_model_matrix)

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

#endif