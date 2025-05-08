#ifndef SHADER_H
#define SHADER_H

#include <glad/gl.h>

struct shader {
  const char* source;
  GLenum type;
};

#define shader(source, type) shadermk(source, type)

struct shader shadermk(const char*, GLenum);

GLuint compile_shader(struct shader);

GLuint load_shader_program(const char* vertex_path, const char* fragment_path);

#endif