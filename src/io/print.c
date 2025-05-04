#include <stdio.h>
#include <stdarg.h>
#include "io/print.h"

void gltprintf(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
  fflush(stdout);
}