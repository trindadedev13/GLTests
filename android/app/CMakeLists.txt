cmake_minimum_required(VERSION 3.22)

project(brut_android)


add_subdirectory("../../core" "${CMAKE_BINARY_DIR}/core_build")

target_compile_definitions(brut_core
    PUBLIC
    BRUT_WINDOW_USE_DISPLAY_SIZE)

target_compile_definitions(brut_core
    PUBLIC
    BRUT_ANDROID)

# Your game and its CMakeLists.txt are in a subfolder named "src"
add_subdirectory(src/main/c)
