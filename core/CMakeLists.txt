cmake_minimum_required(VERSION 3.10)

project(brut_core
    LANGUAGES
    C
    CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/BrutGame.cpp
    src/BrutGameClock.cpp
    src/BrutIWindow.cpp
    src/Buffer/BrutVertexArrayBuffer.cpp
    src/Error/BrutError.cpp
    src/Graphics/BrutColor.cpp
    src/Graphics/Shader/BrutShader.cpp
    src/Graphics/Shader/BrutShadersManager.cpp
    src/Objects/Primitives/BrutCube.cpp
    src/Objects/Primitives/BrutObject.cpp
    src/Objects/Primitives/BrutPyramid.cpp
    src/Objects/Primitives/BrutTerrain.cpp)

set(HEADERS
    include/BrutGame.hpp
    include/BrutGameClock.hpp
    include/BrutIWindow.hpp
    include/Buffer/BrutBuffer.hpp
    include/Buffer/BrutBuffer.tpp
    include/Buffer/BrutVertexArrayBuffer.hpp
    include/Error/BrutError.hpp
    include/Graphics/BrutColor.hpp
    include/Graphics/Shader/BrutShader.hpp
    include/Graphics/Shader/BrutShadersManager.hpp
    include/Objects/Primitives/BrutCube.hpp
    include/Objects/Primitives/BrutObject.hpp
    include/Objects/Primitives/BrutPyramid.hpp
    include/Objects/Primitives/BrutTerrain.hpp
    include/Terminal/TermColor.hpp
    include/BrutConfig.hpp)

find_package(glm REQUIRED)

add_library(
    ${PROJECT_NAME}
    STATIC
    ${SOURCES}
    ${HEADERS})

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    glm::glm
    glad)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
    RUNNING_PATH=$ENV{RUNNING_PATH})

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include)