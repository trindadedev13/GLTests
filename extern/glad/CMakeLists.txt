add_library(
    glad
    include/glad/gl.h
    src/glad/gl.c)

target_link_libraries(
    glad
    PRIVATE
    KHR)

target_include_directories(
    glad
    PUBLIC
    include/)