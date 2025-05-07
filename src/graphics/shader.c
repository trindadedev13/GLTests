#include "graphics/shader.h"

#include <glad/gl.h>
#include <stdio.h>
#include <stdlib.h>

#include "io/file.h"
#include "io/print.h"

GLuint compile_shader(GLenum type, const char* source) {
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);
  return shader;
}

GLuint load_shader_program(const char* vertex_path, const char* fragment_path) {
  char* vertex_src = read_file(vertex_path);
  char* fragment_src = read_file(fragment_path);
  GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_src);
  GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_src);
  GLuint program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);
  free(vertex_src);
  free(fragment_src);
  return program;
}