cmake_minimum_required(VERSION 3.22)

project(brut_core
    LANGUAGES
    C
    CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/BrutGame.cpp
    src/BrutGameClock.cpp
    src/Buffer/BrutVertexArrayBuffer.cpp
    src/Camera/BrutCamera.cpp
    src/Error/BrutError.cpp
    src/FreeTypeGL/BrutFreeTypeGL.cpp
    src/Graphics/BrutColor.cpp
    src/Graphics/Shader/BrutShader.cpp
    src/Graphics/Shader/BrutShadersManager.cpp
    src/Objects/Primitives/BrutCubeCollection.cpp
    src/Objects/Primitives/BrutObject.cpp
    src/Objects/Primitives/BrutPyramid.cpp
    src/Objects/Primitives/2D/BrutSquare.cpp
    src/Objects/Terrain/BrutTerrain.cpp
    src/Objects/Terrain/BrutPlanTerrain.cpp
    src/Perlin/BrutPerlinNoise.cpp
    src/Player/BrutInventory.cpp
    src/Player/BrutInventoryItem.cpp
    src/Player/BrutPlayer.cpp
    src/Window/BrutIWindow.cpp
    src/Window/BrutSDLWindow.cpp)

set(HEADERS
    include/BrutConfig.h
    include/BrutGame.hpp
    include/BrutGameClock.hpp
    include/Assets/BrutIAssetsManager.hpp
    include/Buffer/BrutBuffer.hpp
    include/Buffer/BrutBuffer.tpp
    include/Buffer/BrutVertexArrayBuffer.hpp
    include/Camera/BrutCamera.hpp
    include/Error/BrutError.hpp
    include/FreeTypeGL/BrutFreeTypeGL.hpp
    include/Graphics/BrutColor.hpp
    include/Graphics/Shader/BrutShader.hpp
    include/Graphics/Shader/BrutShadersManager.hpp
    include/Objects/Primitives/BrutCubeCollection.hpp
    include/Objects/Primitives/BrutObject.hpp
    include/Objects/Primitives/BrutPyramid.hpp
    include/Objects/Primitives/2D/BrutSquare.hpp
    include/Objects/Terrain/BrutTerrain.hpp
    include/Objects/Terrain/BrutPlanTerrain.hpp
    include/Perlin/BrutPerlinNoise.hpp
    include/Player/BrutInventory.hpp
    include/Player/BrutInventoryItem.hpp
    include/Player/BrutPlayer.hpp
    include/Terminal/TermColor.h
    include/Window/BrutIWindow.hpp
    include/Window/BrutSDLWindow.hpp
    include/Window/BrutWindowConfig.h)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/CheckPackages.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/CoreDeps.cmake)

add_library(
    ${PROJECT_NAME}
    STATIC
    ${SOURCES}
    ${HEADERS})

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    ${CORE_DEPS})

if (DEFINED RUNNING_PATH)
  target_compile_definitions(${PROJECT_NAME}
      PUBLIC RUNNING_PATH=\"${RUNNING_PATH}\")
endif()

if (DEFINED BRUT_WINDOW_USE_DISPLAY_SIZE)
  target_compile_definitions(${PROJECT_NAME}
      PUBLIC BRUT_WINDOW_USE_DISPLAY_SIZE)
endif()

if (DEFINED BRUT_ANDROID)
  target_compile_definitions(${PROJECT_NAME}
      PUBLIC BRUT_ANDROID)
endif()

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include)
