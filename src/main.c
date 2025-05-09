#include <cglm/cglm.h>
#include <errno.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "config.h"
#include "graphics/color.h"
#include "io/print.h"
#include "objects/cube.h"
#include "renderer.h"
#include "term/tcolor.h"

static void print_running_info() {
  gcgprintf("%sRunning Info:\n%s", T_COLOR_YELLOW, T_COLOR_RESET);
  gcgprintf("%s", T_COLOR_BLUE);

  gcgprintf("---- Platform: %s ----\n", GCG_DEVICE_NAME);
  gcgprintf("---- Environment Path: %s all resources will be used from it. ----\n", GCG_RUNNING_PATH);
  gcgprintf("---- GL Version: %s ---- \n", (const char*) glGetString(GL_VERSION));

  gcgprintf("%s", T_COLOR_RESET);
}

int main() {
  if (!glfwInit())
    return -1;

  struct glrenderer renderer = {};
  if (glrenderer_init_window(&renderer) != EXIT_SUCCESS) {
    gcgperror("Failed to init window.");
    return EXIT_FAILURE;
  }
  glrenderer_configure_window(&renderer);

  if (!gladLoadGL(glfwGetProcAddress)) {
    gcgperror("Failed to initialize GLAD.");
    return EXIT_FAILURE;
  }

  print_running_info();

  struct cube* cb = cube_create();
  if (cb == NULL) {
    gcgperror("Failed to create cube.");
    return EXIT_FAILURE;
  }
  cb->cube_color = COLOR_BLUE;

  // setup project matrix
  float aspect = (float)GL_WINDOW_WIDTH / (float)GL_WINDOW_HEIGHT;
  mat4 matrix_projection;
  glm_perspective(glm_rad(45.0f),      // fovy vertical field of view
                  aspect,              // aspect vision aspect (width / height)
                  1.0f,                // nearz close cutting plane
                  10.0f,               // farz distant cut point
                  matrix_projection);  // dest 4x4 matrix where projection
                                       // matrix will be stored

  // setup view matrix ( camera )
  mat4 matrix_view;
  glm_lookat((vec3){0.0f, 0.0f, -3.0f},  // eye
             (vec3){0.0f, 0.0f, 0.0f},   // center
             (vec3){0.0f, 1.0f, 0.0f},   // up vector
             matrix_view);  // dest 4x4 matrix where will be stored view matrix

  // Model matrix (M)
  mat4 matrix_model;
  glm_mat4_identity(matrix_model);

  srand(time(NULL));
  float last_time = glfwGetTime();
  float time = .5f;

  while (!glfwWindowShouldClose(renderer.window)) {
    float current_time = glfwGetTime();
    float delta_time = current_time - last_time;
    last_time = current_time;
    time += delta_time;

    float factor = (sinf(time) + .5f) / 1.0f;
    color clc = {1.0f * (.5f - factor), 0.0f, 1.0f * factor, 1.0f};
    cb->cube_color = clc;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(COLOR_WHITE.r, COLOR_WHITE.g, COLOR_WHITE.b, COLOR_WHITE.a);

    // calculate MVP matrix
    mat4 matrix_mvp;
    mat4 matrix_temp;
    glm_mat4_mul(matrix_view, matrix_model, matrix_temp);

    glm_mat4_mul(matrix_projection, matrix_temp, matrix_mvp);

    // draw cube

    // first reset cube model matrix
    cube_reset_model_matrix(cb);

    // move cube to 0, 0, 0
    glm_translate(cb->cube_model_matrix, (vec3){0.0f, 0.0f, 0.0f});

    glm_rotate(cb->cube_model_matrix, glm_rad(time * 80.0f),
               (vec3){1.0f, 1.0f, 0.0f});

    glm_scale(cb->cube_model_matrix, (vec3){.2f, .2f, .2f});

    // calculate MVP = matrix_projection * matrix_view * cb_model
    mat4 matrix_temp2;
    glm_mat4_mul(matrix_view, cb->cube_model_matrix, matrix_temp2);
    glm_mat4_mul(matrix_projection, matrix_temp2, matrix_mvp);

    glm_mat4_copy(matrix_mvp, cb->matrix_mvp);
    cube_draw(cb);

    glrenderer_swap_buffers(&renderer);
    glfwPollEvents();
  }

  free(cb);
  glrenderer_end(&renderer);
  return 0;
}