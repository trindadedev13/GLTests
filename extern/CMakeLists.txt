add_subdirectory(KHR)
add_subdirectory(glad)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/CheckPackages.cmake)

if(NOT SDL_FOUND)
  set(SDL_VIDEO ON CACHE BOOL "" FORCE)
  set(SDL_OPENGL ON CACHE BOOL "" FORCE)
  set(SDL_OPENGLES ON CACHE BOOL "" FORCE)
  set(SDL_VIDEO_OPENGL ON CACHE BOOL "" FORCE)
  set(SDL_VIDEO_X11 ON CACHE BOOL "" FORCE)
  set(SDL_VIDEO_OPENGL_GLX ON CACHE BOOL "" FORCE)
  set(SDL_VIDEO_VULKAN OFF CACHE BOOL "" FORCE)
  add_subdirectory(SDL)
endif()

if(NOT GLM_FOUND)
  add_subdirectory(glm)
endif()