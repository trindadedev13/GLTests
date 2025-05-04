#include <stdio.h>
#include <stdlib.h>
#include "io/file.h"

char* read_file(const char* path) {
  FILE* file = fopen(path, "rb");
  if (!file) return NULL;
  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  rewind(file);
  char* data = malloc(size + 1);
  fread(data, 1, size, file);
  data[size] = '\0';
  fclose(file);
  return data;
}