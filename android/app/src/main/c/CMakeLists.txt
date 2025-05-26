cmake_minimum_required(VERSION 3.6)

project(brut_android_src)

add_library(main
    SHARED
    main.cpp)

target_include_directories(main
    PRIVATE
    ${SDL3_SOURCE_DIR}/include)

target_link_libraries(main
    PRIVATE
    SDL3::SDL3)