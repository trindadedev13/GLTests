#ifndef BRUT_BUFFER_HPP
#define BRUT_BUFFER_HPP

#include <cstdlib>
#include <glad/gl.h>

namespace Brut {
template <GLenum T>
class Buffer {
 public:
  Buffer();
  Buffer(const void* data, size_t size);
  ~Buffer();

  Buffer(const Buffer&) = delete;
  Buffer& operator=(const Buffer&) = delete;

  Buffer(Buffer&& other) noexcept;
  Buffer& operator=(Buffer&& other) noexcept;

  void bind();
  void unbind();
  void putData(const void* data, size_t size, GLenum usage = GL_STATIC_DRAW);
  GLuint getID() const;

 private:
  GLuint bufferID = 0;
};

using ArrayBuffer = Buffer<GL_ARRAY_BUFFER>;
using ElementArrayBuffer = Buffer<GL_ELEMENT_ARRAY_BUFFER>;

}  // namespace Brut

#include "Buffer/BrutBuffer.tpp"

#endif