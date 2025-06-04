/* =========================================================================
 * Freetype GL - A C OpenGL Freetype engine
 * Platform:    Any
 * WWW:         http://code.google.com/p/freetype-gl/
 * -------------------------------------------------------------------------
 * Copyright 2011 Nicolas P. Rougier. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY NICOLAS P. ROUGIER ''AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL NICOLAS P. ROUGIER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are
 * those of the authors and should not be interpreted as representing official
 * policies, either expressed or implied, of Nicolas P. Rougier.
 * =========================================================================
 *
 * This class received some changes for Brut.
 * Aquiles Trindade (trindadedev13).
 */

#include "FreeTypeGL/BrutFreeTypeGL.hpp"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

extern "C" {
#include <FreeTypeGL/mat4.h>
}

#include <SDL3/SDL.h>

#include "Assets/BrutIAssetsManager.hpp"
#include "Error/BrutError.hpp"
#include "Graphics/Shader/BrutShader.hpp"
#include "Graphics/Shader/BrutShadersManager.hpp"

namespace Brut {

namespace Ftgl {

#define MAX_STRING_LEN 128

typedef struct {
  float x, y, z;
  float u, v;
  vec4 color;
} vertex_t;

static const char* fontPaths[NUM_FONTS] = {"fonts/amiri-regular.ttf",
                                           "fonts/Liberastika-Regular.ttf",
                                           "fonts/Lobster-Regular.ttf",
                                           "fonts/LuckiestGuy.ttf",
                                           "fonts/OldStandard-Regular.ttf",
                                           "fonts/SourceCodePro-Regular.ttf",
                                           "fonts/SourceSansPro-Regular.ttf",
                                           "fonts/Vera.ttf",
                                           "fonts/VeraMoBd.ttf",
                                           "fonts/VeraMoBI.ttf",
                                           "fonts/VeraMono.ttf"};

void add_text(vertex_buffer_t* m_pBuffer,
              texture_font_t* pFont,
              const char* text,
              vec2 pen,
              vec4 fg_color_1,
              vec4 fg_color_2) {
  for (size_t i = 0; i < strlen(text); ++i) {
    texture_glyph_t* glyph = texture_font_get_glyph(pFont, text + i);
    float kerning = 0.0f;
    if (i > 0) {
      kerning = texture_glyph_get_kerning(glyph, text + i - 1);
    }
    pen.x += kerning;

    /* Actual glyph */
    float x0 = (pen.x + glyph->offset_x);
    float y0 = (float)((int)(pen.y + glyph->offset_y));
    float x1 = (x0 + glyph->width);
    float y1 = (float)((int)(y0 - glyph->height));
    float s0 = glyph->s0;
    float t0 = glyph->t0;
    float s1 = glyph->s1;
    float t1 = glyph->t1;
    GLuint index = (GLuint)m_pBuffer->vertices->size;
    GLuint indices[] = {index, index + 1, index + 2,
                        index, index + 2, index + 3};
    vertex_t vertices[] = {{(float)((int)x0), y0, 0, s0, t0, fg_color_1},
                           {(float)((int)x0), y1, 0, s0, t1, fg_color_2},
                           {(float)((int)x1), y1, 0, s1, t1, fg_color_2},
                           {(float)((int)x1), y0, 0, s1, t0, fg_color_1}};
    vertex_buffer_push_back_indices(m_pBuffer, indices, 6);
    vertex_buffer_push_back_vertices(m_pBuffer, vertices, 4);
    pen.x += glyph->advance_x;
  }
}

FontRenderer::FontRenderer(std::shared_ptr<ShadersManager> _shadersManager,
                           IAssetsManager* _assetsManager,
                           int _windowWidth,
                           int _windowHeight)
    : shadersManager{_shadersManager}, assetsManager{_assetsManager} {
  initFontRenderer(_windowWidth, _windowHeight);
}

FontRenderer::~FontRenderer() {}

void FontRenderer::initFontRenderer(int windowWidth, int windowHeight) {
  m_pAtlas = texture_atlas_new(1024, 1024, 1);
  m_pBuffer = vertex_buffer_new("vertex:3f,tex_coord:2f,color:4f");

  loadFonts();

  glGenTextures(1, &m_pAtlas->id);
  glBindTexture(GL_TEXTURE_2D, m_pAtlas->id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, (GLsizei)m_pAtlas->width,
               (GLsizei)m_pAtlas->height, 0, GL_RED, GL_UNSIGNED_BYTE,
               m_pAtlas->data);

  auto shaderOp = shadersManager->get("freeTypeGL");
  if (!shaderOp) {
    fatalError("Failed to get freeTypeGL shader");
  }
  shader = *shaderOp;

  mat4_set_identity(&m_model);
  mat4_set_identity(&m_view);
  mat4_set_orthographic(&m_projection, 0, (float)windowWidth, 0,
                        (float)windowHeight, -1, 1);
}

void FontRenderer::loadFonts() {
  for (int i = 0; i < NUM_FONTS; i++) {
    m_pFonts[i] = loadFont(fontPaths[i]);

    if (!m_pFonts[i]) {
      printf("Error loading fonts '%s'\n", fontPaths[i]);
      exit(0);
    }
  }
}

texture_font_t* FontRenderer::loadFont(const std::string& path) {
  std::vector<int8_t> data = assetsManager->readBinaryFile(path);
  if (data.empty()) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load font %s\n",
                 path.c_str());
    return nullptr;
  }
  texture_font_t* font = texture_font_new_from_memory(
      m_pAtlas, 64, reinterpret_cast<const void*>(data.data()), data.size());
  if (font == nullptr) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Failed to create font from memory %s\n", path.c_str());
    return nullptr;
  }
  return font;
}

void FontRenderer::renderText(FONT_TYPE fontType,
                              const Color& topColor,
                              const Color& bottomColor,
                              const glm::vec2& pos,
                              const std::string& text) {
  vec2 pen = {{pos.x, pos.y}};

  if (fontType >= NUM_FONTS) {
    printf("Invalid font type index %d\n", fontType);
    exit(0);
  }

  texture_font_t* pFont = m_pFonts[fontType];

  pFont->rendermode = RENDER_NORMAL;
  pFont->outline_thickness = 0;
  vertex_buffer_clear(m_pBuffer);

  vec4 topColor_v4 = vec4{topColor.r, topColor.g, topColor.b, topColor.a};
  vec4 bottomColor_v4 =
      vec4{bottomColor.r, bottomColor.g, bottomColor.b, bottomColor.a};
  add_text(m_pBuffer, pFont, text.c_str(), pen, topColor_v4, bottomColor_v4);

  glEnable(GL_BLEND);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_pAtlas->id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, (GLsizei)m_pAtlas->width,
               (GLsizei)m_pAtlas->height, 0, GL_RED, GL_UNSIGNED_BYTE,
               m_pAtlas->data);

  shader->bind();

  shader->sendUniformData("tex", 0);
  shader->sendUniformData("model", m_model.data);
  shader->sendUniformData("view", m_view.data);
  shader->sendUniformData("projection", m_projection.data);
  vertex_buffer_render(m_pBuffer, GL_TRIANGLES);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
}

void FontRenderer::renderText(FONT_TYPE fontType,
                              const Color& color,
                              const glm::vec2& pos,
                              const std::string& text) {
  renderText(fontType, color, color, pos, text);
}

}  // namespace Ftgl

}  // namespace Brut