add_library(FreeTypeGL
    src/font-manager.c
    src/shader.c
    src/mat4.c
    src/text-buffer.c
    src/texture-atlas.c
    src/texture-font.c
    src/vector.c
    src/vertex-attribute.c
    src/vertex-buffer.c
    src/ftgl-utils.c
    src/utf8-utils.c
    src/edtaa3func.c
    src/distance-field.c
    src/platform.c
    include/FreeTypeGL/platform.h
    include/FreeTypeGL/edtaa3func.h
    include/FreeTypeGL/distance-field.h
    include/FreeTypeGL/shader.h
    include/FreeTypeGL/markup.h
    include/FreeTypeGL/texture-atlas.h
    include/FreeTypeGL/vertex-attribute.h
    include/FreeTypeGL/vec234.h
    include/FreeTypeGL/mat4.h
    include/FreeTypeGL/text-buffer.h
    include/FreeTypeGL/texture-font.h
    include/FreeTypeGL/vertex-buffer.h
    include/FreeTypeGL/opengl.h
    include/FreeTypeGL/vector.h
    include/FreeTypeGL/font-manager.h
    include/FreeTypeGL/ftgl-utils.h
    include/FreeTypeGL/utf8-utils.h
    include/FreeTypeGL/freetype-gl-errdef.h)

if(DEFINED ENV{BRUT_ANDROID})
  find_library(log-lib log)

  target_link_libraries(FreeTypeGL
      PUBLIC
      glad
      freetype
      log)
else()
  target_link_libraries(FreeTypeGL
    PUBLIC
    glad
    freetype)
endif()

target_include_directories(FreeTypeGL
    PUBLIC
    include/)