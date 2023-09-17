#include "engine/Image.hpp"
#include <cstring>

using Engine::Image;

Image::Image(glm::ivec2 size, const uint32_t* data) {
  this->size = size;
  this->data = const_cast<uint32_t*>(data);

  this->allocate();
}

Image::~Image() {
  if (this->handle != 0)
    this->release();
}

void Image::bind() {
  if (this->isBound())
    return;
  this->bound = true;
  glBindTexture(GL_TEXTURE_2D, this->handle);
}

void Image::unbind() {
  if (!this->isBound())
    return;
  this->bound = false;
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Image::allocate(bool force) {
  if (this->handle != 0 && !force)
    return;
  if (this->handle != 0)
    this->release();
  glGenTextures(1, &this->handle);
  uint32_t* newBuffer = new uint32_t[this->size.x * this->size.y];
  if (this->data != nullptr) {
    std::memmove(newBuffer, this->data, this->size.x * this->size.y);
    delete this->data;
  }
  else
    std::memset(newBuffer, 0, this->size.x * this->size.y);
  this->data = newBuffer;
}

void Image::release() {
  if (this->handle == 0)
    return;
  glDeleteTextures(1, &this->handle);
  this->handle = 0;
  delete this->data;
  this->data = nullptr;
}

void Image::render() {
  // if (this->isBound())
    // return;
  glDrawPixels(this->size.x, this->size.y, GL_RGBA, GL_UNSIGNED_BYTE, this->data);
  // this->bind();
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->size.x, this->size.y, 0, GL_RGBA, GL_UNSIGNED_INT, this->data);
  // this->unbind();
}

void Image::setPixel(glm::ivec2 pos, uint32_t color) const {
  if (pos.x < 0 || pos.y < 0 || pos.x >= this->size.x || pos.y >= this->size.y)
    return;
  this->data[pos.x + pos.y * this->size.x] = color;
}

void Image::resize(glm::ivec2 size) {
  if (this->size == size)
    return;
  this->size = size;
  this->allocate();
}