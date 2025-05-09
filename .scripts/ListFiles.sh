#!/usr/bin/bash

for file in $(find include/ -name '*.[h]' -o -name '*.hpp'); do
  echo "    $file" >> headers.txt
done

echo "Headers saved in headers.txt"

for file in $(find src/ -name '*.c' -o -name '*.cpp'); do
  echo "    $file" >> sources.txt
done

echo "Sources saved in sources.txt"