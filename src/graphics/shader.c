#include "graphics/shader.h"

#include <glad/gl.h>
#include <stdio.h>
#include <stdlib.h>

#include "io/file.h"
#include "io/print.h"

struct shader shadermk(const char* source, GLenum type) {
  struct shader s;
  s.source = source;
  s.type = type;
  return s;
}

GLuint compile_shader(struct shader s) {
  GLuint shader = glCreateShader(s.type);
  glShaderSource(shader, 1, &s.source, NULL);
  glCompileShader(shader);
  return shader;
}

GLuint load_shader_program(const char* vertex_path, const char* fragment_path) {
  char* vertex_src = read_file(vertex_path);
  char* fragment_src = read_file(fragment_path);
  GLuint vertex_shader = compile_shader(shader(vertex_src, GL_VERTEX_SHADER));
  GLuint fragment_shader = compile_shader(shader(fragment_src, GL_FRAGMENT_SHADER));
  GLuint program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);
  free(vertex_src);
  free(fragment_src);
  return program;
}