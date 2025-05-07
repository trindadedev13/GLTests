#include "io/print.h"

#include <stdarg.h>
#include <stdio.h>

void gltsprintf(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
  fflush(stdout);
}