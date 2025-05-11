#!/usr/bin/bash

export RUNNING_PATH="\"$(pwd)\""
export PLATFORM=BRUT_PLATFORM_LINUX

# compile
if [ "$1" = "-c" ]; then
  rm -rf build
fi

mkdir build
cd build

cmake ..
make

cp brut ../