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
    src/main.cpp
    src/BrutGame.cpp
    src/BrutWindow.cpp
    src/Error/BrutError.cpp
    src/Graphics/BrutColor.cpp
    src/Graphics/BrutShader.cpp
    src/Objects/BrutCube.cpp)

set(HEADERS
    include/BrutGame.hpp
    include/BrutWindow.hpp
    include/Buffer/BrutBuffer.hpp
    include/Buffer/BrutBuffer.tpp
    include/Error/BrutError.hpp
    include/Graphics/BrutColor.hpp
    include/Graphics/BrutShader.hpp
    include/Objects/BrutCube.hpp
    include/Terminal/TermColor.hpp
    include/config.h)

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
    glad
    OpenGL::GL
    glfw
    ${CMAKE_DL_LIBS})

target_include_directories(${PROJECT_NAME}
    PUBLIC
    include/)