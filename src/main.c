#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include "config.h"
#include "renderer.h"
#include "io/print.h"
#include "graphics/color.h"
#include "objects/cube.h"

int main() {
  if (!glfwInit()) return -1;

  gltprintf("Running at path: %s all resources will be used from it.\n", GLT_RUNNING_PATH);

  struct glrenderer renderer = {};
  if (glrenderer_init_window(&renderer) != EXIT_SUCCESS) {
    gltprintf("Failed to init window\n");
    return EXIT_FAILURE;
  }
  glrenderer_configure_window(&renderer);

  if (!gladLoadGL(glfwGetProcAddress)) {
    fprintf(stderr, "Failed to initialize GLAD\n");
    fflush(stderr);
    return EXIT_FAILURE;
  }

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  struct cube* cb = cube_create();
  if (cb == NULL) {
    gltprintf("Error: %s", strerror(errno));
    return EXIT_FAILURE;
  }
  cb->cube_color = COLOR_RED;

  // GLM: Create projection matrix (P)
  float aspect = (float) GL_WINDOW_WIDTH / (float) GL_WINDOW_HEIGHT;
  mat4 matrix_projection;
  glm_perspective(
      glm_rad(45.0f),      // fovy vertical field of view
      aspect,              // aspect vision aspect (width / height)
      1.0f,                // nearz close cutting plane
      10.0f,               // farz distant cut point
      matrix_projection);  // dest 4x4 matrix where projection matrix will be stored

  // GLM: Create view matrix (V) - Camera
  mat4 matrix_view;
  glm_lookat(
      (vec3){ 0.0f, 0.0f, -3.0f },   // eye
      (vec3){ 0.0f, 0.0f,  0.0f  },  // center 
      (vec3){ 0.0f, 1.0f,  0.0f  },  // up vector
      matrix_view);                  // dest 4x4 matrix where will be stored view matrix

  // Model matrix (M)
  mat4 mmodel;
  glm_mat4_identity(mmodel);

  while (!glfwWindowShouldClose(renderer.window)) {
    float time = glfwGetTime();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(
        COLOR_WHITE.r,
        COLOR_WHITE.g,
        COLOR_WHITE.b,
        COLOR_WHITE.a);

    // calculate MVP matrix
    mat4 matrix_mvp;
    mat4 matrix_temp;
    glm_mat4_mul(
        matrix_view,
        mmodel,
        matrix_temp);

    glm_mat4_mul(
        matrix_projection,
        matrix_temp,
        matrix_mvp);

    // draw cube

    // move cube to 0, 0, 0
    glm_translate(
        cb->cube_model_matrix,
        (vec3) { 0.0f, 0.0f, 0.0f });

    glm_rotate(
        cb->cube_model_matrix,
        glm_rad(time * 50.0f),
        (vec3) { 1.0f, 1.0f, 0.0f });

    glm_scale(
        cb->cube_model_matrix,
        (vec3) { .5f, .5f, .5f });

    // calculate MVP = matrix_projection * matrix_view * cb_model
    mat4 matrix_temp2;
    glm_mat4_mul(
        matrix_view,
        cb->cube_model_matrix,
        matrix_temp2);
    glm_mat4_mul(
        matrix_projection,
        matrix_temp2,
        matrix_mvp);

    cb->mvp_matrix = (GLfloat*) matrix_mvp;
    cube_draw(cb);

    glrenderer_swap_buffers(&renderer);
    glfwPollEvents();
  }

  free(cb);
  glrenderer_end(&renderer);
  return 0;
}