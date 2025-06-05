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
 * ========================================================================= */

#ifndef BRUT_FREE_TYPE_GL_HPP
#define BRUT_FREE_TYPE_GL_HPP

#include <memory>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

extern "C" {
#include <FreeTypeGL/font-manager.h>
#include <FreeTypeGL/markup.h>
#include <FreeTypeGL/texture-font.h>
#include <FreeTypeGL/text-buffer.h>
#include <FreeTypeGL/mat4.h>
#include <FreeTypeGL/shader.h>
}

#include "Assets/BrutIAssetsManager.hpp"
#include "Graphics/BrutColor.hpp"
#include "Graphics/Shader/BrutShader.hpp"
#include "Graphics/Shader/BrutShadersManager.hpp"

namespace Brut {

namespace Ftgl {

enum FONT_TYPE {
  FONT_TYPE_AMIRI,
  FONT_TYPE_LIBERASTIKA,
  FONT_TYPE_LOBSTER,
  FONT_TYPE_LUCKIEST_GUY,
  FONT_TYPE_OLD_STANDARD,
  FONT_TYPE_SOURCE_CODE_PRO,
  FONT_TYPE_SOURCE_SANS_PRO,
  FONT_TYPE_VERA,
  FONT_TYPE_VERA_MOBD,
  FONT_TYPE_VERA_MOBI,
  FONT_TYPE_VERA_MONO,
  NUM_FONTS
};

class FontRenderer {
 public:
  FontRenderer(std::shared_ptr<ShadersManager>, IAssetsManager*, int, int);
  ~FontRenderer();

  void renderText(FONT_TYPE fontType,
                  const Color& topColor,
                  const Color& bottomColor,
                  const glm::vec2& pos,
                  const std::string& text);

  void renderText(FONT_TYPE fontType,
                  const Color& color,
                  const glm::vec2& pos,
                  const std::string& text);

 private:
  void initFontRenderer(int windowWidth, int windowHeight);
  void loadFonts();
  texture_font_t* loadFont(const std::string&);

  texture_atlas_t* m_pAtlas = NULL;
  vertex_buffer_t* m_pBuffer = NULL;
  texture_font_t* m_pFonts[NUM_FONTS] = {};
  GLuint m_shaderProg = -1;
  mat4 m_model, m_view, m_projection;

  std::shared_ptr<ShadersManager> shadersManager;
  std::shared_ptr<Shader> shader;
  IAssetsManager* assetsManager;
};

}  // namespace Ftgl

}  // namespace Brut

#endif