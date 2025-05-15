add_library(
    glad
    include/glad/glad.h
    src/glad/glad.c)

target_link_libraries(glad
    PUBLIC
    KHR)

target_include_directories(
    glad
    PUBLIC
    include/)