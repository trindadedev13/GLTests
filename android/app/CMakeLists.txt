cmake_minimum_required(VERSION 3.6)

project(brut_android)

add_subdirectory(SDL)

# Your game and its CMakeLists.txt are in a subfolder named "src"
add_subdirectory(src/main/c)