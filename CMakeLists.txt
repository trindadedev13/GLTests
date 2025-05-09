cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME brutonium)

project(${PROJECT_NAME}
    LANGUAGES
    C
    CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(extern EXCLUDE_FROM_ALL)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

set(SOURCES
    src/graphics/shader.c
    src/graphics/color.c
    src/main.c
    src/renderer.c
    src/objects/cube.c
    src/io/file.c
    src/io/print.c)

set(HEADERS
    include/term/tcolor.h
    include/config.h
    include/graphics/shader.h
    include/graphics/color.h
    include/objects/cube.h
    include/io/file.h
    include/io/print.h
    include/renderer.h)

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS})

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
    $ENV{PLATFORM})

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
    RUNNING_PATH=$ENV{RUNNING_PATH})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    m
    cglm
    glad
    OpenGL::GL
    glfw
    ${CMAKE_DL_LIBS})

target_include_directories(${PROJECT_NAME}
    PUBLIC
    include/)