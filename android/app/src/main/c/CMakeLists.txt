cmake_minimum_required(VERSION 3.22)

project(brut_android_src)

if(NOT TARGET SDL3::SDL3)
    find_package(SDL3 CONFIG)
endif()

if(NOT TARGET SDL3::SDL3)
    find_library(SDL3_LIBRARY NAMES "SDL3")
    find_path(SDL3_INCLUDE_DIR NAMES "SDL3/SDL.h")
    add_library(SDL3::SDL3 UNKNOWN IMPORTED)
    set_property(TARGET SDL3::SDL3 PROPERTY IMPORTED_LOCATION "${SDL3_LIBRARY}")
    set_property(TARGET SDL3::SDL3 PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${SDL3_INCLUDE_DIR}")
endif()

if(NOT TARGET SDL3::SDL3)
    message(FATAL_ERROR "Cannot find SDL3.

Possible ways to fix this:
- Use a SDL3 Android aar archive, and configure gradle to use it: prefab is required.
- Add add_subdirectory(path/to/SDL) to your CMake script, and make sure a vendored SDL is present there.
")
endif()

set(SOURCES
    main.cpp
    Assets/BrutAndroidAssetsManager.cpp
    Assets/jni/brut_android_assets_manager_jni.c)

set(HEADERS
    Assets/BrutAndroidAssetsManager.hpp
    Assets/jni/brut_android_assets_manager_jni.h)

add_library(main
    SHARED
    ${SOURCES}
    ${HEADERS})

find_library(log-lib log)

target_include_directories(main
    PRIVATE
    ${SDL3_SOURCE_DIR}/include)

target_link_libraries(main
    PRIVATE
    android
    log
    brut_core
    SDL3::SDL3)
