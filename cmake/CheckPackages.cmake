### Checks if the device have SDL3 and glm installed.

cmake_minimum_required(VERSION 3.22)

find_package(SDL3 QUIET)
if(SDL3_FOUND)
  set(SDL_FOUND TRUE CACHE BOOL "SDL3 found")
else()
  set(SDL_FOUND FALSE CACHE BOOL "SDL3 not found")
endif()

find_package(glm QUIET)
if(glm_FOUND)
  set(GLM_FOUND TRUE CACHE BOOL "GLM found")
else()
  set(GLM_FOUND FALSE CACHE BOOL "GLM not found")
endif()