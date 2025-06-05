cmake_minimum_required(VERSION 3.22)

if(NOT TARGET glad OR NOT TARGET glm::glm OR NOT TARGET SDL3::SDL3 OR NOT TARGET FreeTypeGL)
  add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../extern"
                   "${CMAKE_BINARY_DIR}/extern_build")
endif()

set(CORE_DEPS
    glad
    glm::glm
    SDL3::SDL3
    FreeTypeGL)