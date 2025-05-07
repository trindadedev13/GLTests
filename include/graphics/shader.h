#ifndef SHADER_H
#define SHADER_H

#include <glad/gl.h>

GLuint compile_shader(GLenum type, const char* source);

GLuint load_shader_program(const char* vertex_path, const char* fragment_path);

#endif