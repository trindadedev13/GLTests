#include "objects/cube.h"

#include <cglm/cglm.h>
#include <stdlib.h>

#include "config.h"
#include "graphics/shader.h"
#include "io/print.h"

static const GLfloat cube_vertices[] = {
    -1, -1, -1,  // 0
    1,  -1, -1,  // 1
    1,  1,  -1,  // 2
    -1, 1,  -1,  // 3
    -1, -1, 1,   // 4
    1,  -1, 1,   // 5
    1,  1,  1,   // 6
    -1, 1,  1    // 7
};

static const GLuint cube_indices[] = {
    // front
    4, 5, 6, 6, 7, 8,

    // back
    0, 1, 2, 2, 3, 0,

    // left
    0, 4, 7, 7, 3, 0,

    // right
    1, 5, 6, 6, 2, 1,

    // top
    3, 7, 6, 6, 2, 3,

    // bottom
    0, 4, 5, 5, 1, 0};

GLuint cube_shader_program() {
  char scfp[512];
  char scvp[512];

  snprintf(scfp, sizeof(scfp), "%s/shaders/cube/cube.vert", GCG_RUNNING_PATH);
  snprintf(scvp, sizeof(scvp), "%s/shaders/cube/cube.frag", GCG_RUNNING_PATH);

  return load_shader_program(scfp, scvp);
}

struct cube* cube_create() {
  struct cube* cb = malloc(sizeof(struct cube));
  if (!cb)
    return NULL;
  cb->cube_vao = 0;
  cb->cube_vbo = 0;
  cb->cube_ebo = 0;
  cb->cube_color = COLOR_WHITE;
  cb->cube_shader_program = cube_shader_program();
  glm_mat4_identity(cb->cube_model_matrix);

  glGenVertexArrays(1, &cb->cube_vao);
  glGenBuffers(1, &cb->cube_vbo);
  glGenBuffers(1, &cb->cube_ebo);

  glBindVertexArray(cb->cube_vao);

  // VBO
  glBindBuffer(GL_ARRAY_BUFFER, cb->cube_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices,
               GL_STATIC_DRAW);

  // EBO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cb->cube_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices,
               GL_STATIC_DRAW);

  // shader attribute vertex
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (void*)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);
  return cb;
}

void cube_draw(struct cube* cb) {
  glUseProgram(cb->cube_shader_program);

  glBindVertexArray(cb->cube_vao);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (void*)0);

  GLint color_location =
      glGetUniformLocation(cb->cube_shader_program, "uColor");
  GLint mvp_location =
      glGetUniformLocation(cb->cube_shader_program, "uMVPMatrix");

  if (color_location != -1) {
    glUniform4f(color_location, cb->cube_color.r, cb->cube_color.g,
                cb->cube_color.b, cb->cube_color.a);
  }

  if (mvp_location != -1) {
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE,
                       (const GLfloat*)cb->matrix_mvp);
  }

  // Draw
  glDrawElements(GL_TRIANGLES, sizeof(cube_indices) / sizeof(GLuint),
                 GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void cube_reset_model_matrix(struct cube* cb) {
  glm_mat4_identity(cb->cube_model_matrix);
}