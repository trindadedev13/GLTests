#include "Buffer/BrutVertexArrayBuffer.hpp"

#include <glad/glad.h>

namespace Brut {

VertexArrayBuffer::VertexArrayBuffer() {
  glGenVertexArrays(1, &bufferID);
}

VertexArrayBuffer::~VertexArrayBuffer() {
  glDeleteVertexArrays(1, &bufferID);
}

VertexArrayBuffer::VertexArrayBuffer(VertexArrayBuffer&& other) noexcept
    : bufferID(other.bufferID) {
  other.bufferID = 0;
}

VertexArrayBuffer& VertexArrayBuffer::operator=(
    VertexArrayBuffer&& other) noexcept {
  if (this != &other) {
    if (bufferID != 0)
      glDeleteVertexArrays(1, &bufferID);
    bufferID = other.bufferID;
    other.bufferID = 0;
  }
  return *this;
}

void VertexArrayBuffer::bind() {
  glBindVertexArray(bufferID);
}

void VertexArrayBuffer::unbind() {
  glBindVertexArray(0);
}

}  // namespace Brut