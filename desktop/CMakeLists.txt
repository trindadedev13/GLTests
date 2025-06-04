cmake_minimum_required(VERSION 3.22)

project(brut_desktop
    LANGUAGES
    C
    CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(DESKTOP_SOURCES
    src/main.cpp
    src/Assets/BrutDesktopAssetsManager.cpp)

set(DESKTOP_HEADERS
    include/Assets/BrutDesktopAssetsManager.hpp)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/CheckPackages.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/CoreDeps.cmake)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../core
    ${CMAKE_BINARY_DIR}/core_build)

add_executable(${PROJECT_NAME}
    ${DESKTOP_SOURCES}
    ${DESKTOP_HEADERS})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ${CORE_DEPS}
    brut_core)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_SOURCE_DIR}/../core/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include)
