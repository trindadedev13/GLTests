#include "Buffer/BrutBuffer.hpp"

namespace Brut {

template <GLenum T>
Buffer<T>::Buffer() {
  glGenBuffers(1, &bufferID);
  glBindBuffer(T, bufferID);
}

template <GLenum T>
Buffer<T>::Buffer(const void* data, size_t size) {
  glGenBuffers(1, &bufferID);
  glBindBuffer(T, bufferID);
  glBufferData(T, size, data, GL_STATIC_DRAW);
}

template <GLenum T>
Buffer<T>::~Buffer() {
  if (bufferID != 0)
    glDeleteBuffers(1, &bufferID);
}

template <GLenum T>
Buffer<T>::Buffer(Buffer&& other) noexcept : bufferID(other.bufferID) {
  other.bufferID = 0;
}

template <GLenum T>
Buffer<T>& Buffer<T>::operator=(Buffer&& other) noexcept {
  if (this != &other) {
    if (bufferID != 0)
      glDeleteBuffers(1, &bufferID);
    bufferID = other.bufferID;
    other.bufferID = 0;
  }
  return *this;
}

template <GLenum T>
void Buffer<T>::bind() {
  glBindBuffer(T, bufferID);
}

template <GLenum T>
void Buffer<T>::unbind() {
  glBindBuffer(T, 0);
}

template <GLenum T>
void Buffer<T>::putData(const void* data, size_t size, GLenum usage) {
  glBindBuffer(T, bufferID);
  glBufferData(T, size, data, usage);
}

template <GLenum T>
GLuint Buffer<T>::getID() const {
  return bufferID;
}

}  // namespace Brut