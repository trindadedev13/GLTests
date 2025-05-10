#ifndef BRUT_VERTEX_ARRAY_BUFFER
#define BRUT_VERTEX_ARRAY_BUFFER

#include <glad/gl.h>

namespace Brut {

class VertexArrayBuffer {
 public:
  VertexArrayBuffer();
  ~VertexArrayBuffer();

  VertexArrayBuffer(const VertexArrayBuffer&) = delete;
  VertexArrayBuffer& operator=(const VertexArrayBuffer&) = delete;

  VertexArrayBuffer(VertexArrayBuffer&& other) noexcept;
  VertexArrayBuffer& operator=(VertexArrayBuffer&& other) noexcept;

  void bind();
  void unbind();

 private:
  GLuint bufferID = 0;
};

}  // namespace Brut

#endif