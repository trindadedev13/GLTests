cmake_minimum_required(VERSION 3.10)

project(brut_desktop
    LANGUAGES
    C
    CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

set(DESKTOP_SOURCES
    src/main.cpp
    src/BrutDesktopWindow.cpp
    src/BrutDesktopInputHandler)

set(DESKTOP_HEADERS
    include/BrutDesktopWindow.hpp
    include/BrutDesktopInputHandler)

add_executable(${PROJECT_NAME}
    ${DESKTOP_SOURCES}
    ${DESKTOP_HEADERS})

find_package(glm REQUIRED)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    brut_core
    glad
    glfw
    OpenGL::GL
    glm::glm)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
    $ENV{PLATFORM})

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/core/include)