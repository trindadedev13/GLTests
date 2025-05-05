#include <stdlib.h>
#include <glad/gl.h>
#include <cglm/cglm.h>
#include "config.h"
#include "graphics/shader.h"
#include "objects/cube.h"

static const GLfloat cube_vertices[] = {
    // Front
    -1, -1,  1,  1, -1,  1,  1,  1,  1,
    -1, -1,  1,  1,  1,  1, -1,  1,  1,
    // Back
    -1, -1, -1, -1,  1, -1,  1,  1, -1,
    -1, -1, -1,  1,  1, -1,  1, -1, -1,
    // Left
    -1, -1, -1, -1, -1,  1, -1,  1,  1,
    -1, -1, -1, -1,  1,  1, -1,  1, -1,
    // Right
     1, -1, -1,  1,  1, -1,  1,  1,  1,
     1, -1, -1,  1,  1,  1,  1, -1,  1,
    // Top
    -1,  1, -1, -1,  1,  1,  1,  1,  1,
    -1,  1, -1,  1,  1,  1,  1,  1, -1,
    // Bottom
    -1, -1, -1,  1, -1, -1,  1, -1,  1,
    -1, -1, -1,  1, -1,  1, -1, -1,  1
};

GLuint cube_shader_program() {
  char scfp[512];
  char scvp[512];

  snprintf(scfp, sizeof(scfp), "%s/shaders/cube/cube.vert", GLT_RUNNING_PATH);
  snprintf(scvp, sizeof(scvp), "%s/shaders/cube/cube.frag", GLT_RUNNING_PATH);

  return load_shader_program(scfp, scvp);
}

struct cube* cube_create() {
  struct cube* cb = malloc(sizeof(struct cube));
  if (!cb) return NULL;
  cb->cube_vao = 0;
  cb->cube_vbo = 0;
  cb->cube_color = COLOR_WHITE;
  cb->cube_shader_program = cube_shader_program();
  glm_mat4_identity(cb->cube_model_matrix);

  glGenVertexArrays(1, &cb->cube_vao);
  glGenBuffers(1, &cb->cube_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, cb->cube_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(
      0,
      3,
      GL_FLOAT,
      GL_FALSE,
      3 * sizeof(GLfloat),
      (void*) 0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);
  return cb;
}

void cube_draw(struct cube* cb) {
  glUseProgram(cb->cube_shader_program);

  glBindVertexArray(cb->cube_vao);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(
      0,
      3,
      GL_FLOAT,
      GL_FALSE,
      3 * sizeof(GLfloat),
      (void*) 0);

  GLint color_location = glGetUniformLocation(cb->cube_shader_program, "uColor");
  GLint mvp_location = glGetUniformLocation(cb->cube_shader_program, "uMVPMatrix");

  if (color_location != -1) {
    glUniform4f(
        color_location,
        cb->cube_color.r,
        cb->cube_color.g,
        cb->cube_color.b,
        cb->cube_color.a);
  }

  if (mvp_location != -1) {
    glUniformMatrix4fv(
        mvp_location,
        1,
        GL_FALSE,
        (const GLfloat*) cb->mvp_matrix);
  }

  // Draw
  glDrawArrays(GL_TRIANGLES, 0, 6*2*3);  // 6 faces * 2 triangles * 3 vertices
  glBindVertexArray(0);
}