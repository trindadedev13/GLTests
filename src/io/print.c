#include "io/print.h"

#include <stdarg.h>
#include <stdio.h>

void gcgprintf(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
  fflush(stdout);
}

void gcgprintferr(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
  fflush(stderr);
}

void gcgperror(const char* s) {
  perror(s);
  fflush(stderr);
}