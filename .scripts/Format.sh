#!/usr/bin/bash

for file in $(find . -name '*.c' -o -name '*.h' -o -name '*.cpp' -o -name '*.hpp' -o -name '*.tpp' -o -name '*.java' -o -name '*.kt'); do
  if [[ "$file" != *"/.git/"* && "$file" != *"/.git/"*/* && \
      "$file" != *"/.scripts/"* && "$file" != *"/.scripts/"*/* && \
      "$file" != *"/extern/"* && "$file" != *"/extern/"*/* && \
      "$file" != *".cxx"* && "$file" != *".cxx"*/* && \
      "$file" != *"/build/"* && "$file" != *"/build/"*/* ]]; then
    clang-format -i "$file"
    echo "$file formatted!"
  fi
done
