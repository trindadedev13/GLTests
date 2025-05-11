cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(Brut)

find_package(SDL3 REQUIRED)
include_directories(${SDL3_INCLUDE_DIRS})
link_directories(${SDL3_LIBRARY_DIRS})

set(SOURCES
    src/cpp/main.cpp
    src/cpp/BrutAndroidWindow.cpp)

set(HEADERS
    src/cpp/BrutAndroidWindow.hpp)

include_directories(${HEADERS})

add_subdirectory(${CMAKE_SOURCE_DIR}/../../extern/glad
    ${CMAKE_BINARY_DIR}/glad_build)
add_subdirectory(${CMAKE_SOURCE_DIR}/../../core
    ${CMAKE_BINARY_DIR}/core_build)

add_library(main SHARED ${SOURCES})

target_include_directories(main PUBLIC
    ${CMAKE_SOURCE_DIR}/../../core/include)

target_link_libraries(main
    core
    glad
    ${SDL3_LIBRARIES})