#ifndef PRINT_H
#define PRINT_H

#include <stdarg.h>

void gltsprintf(const char* fmt, ...);

void gltsprinterr(const char* fmt, ...);

void gltsperror(const char*);

#endif