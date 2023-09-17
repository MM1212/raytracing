#pragma once

// GLFW Color Buffer Wrapper for OpenGL3

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Engine {
  class Image {
  public:
    Image(glm::ivec2 size, const uint32_t* data = nullptr);
    ~Image();
    void setPixel(glm::ivec2 pos, uint32_t color) const;
    void bind();
    void unbind();
    inline bool isBound() const { return this->bound; }
    
    template <typename T>
    T getPixel(glm::ivec2 pos) const {
      if (pos.x < 0 || pos.y < 0 || pos.x >= this->size.x || pos.y >= this->size.y)
        return T{};
      return reinterpret_cast<T*>(this->data)[pos.x + pos.y * this->size.x];
    }
    
    template <glm::uvec4>
    glm::uvec4 getPixel(glm::ivec2 pos) const {
      uint32_t pixel = this->getPixel<uint32_t>(pos);
      return glm::uvec4{
        (pixel & 0xFF000000) >> 24,
        (pixel & 0x00FF0000) >> 16,
        (pixel & 0x0000FF00) >> 8,
        (pixel & 0x000000FF)
      };
    }
    glm::ivec2 getSize() const { return this->size; }
    const uint32_t* getData() const { return this->data; }
    void setData(const uint32_t* data) { this->data = const_cast<uint32_t*>(data); }
    void resize(glm::ivec2 size);
    void render();
    void allocate(bool force = false);
    void release();
  private:
    glm::ivec2 size = glm::ivec2{ 0, 0 };
    uint32_t* data = nullptr;
    GLuint handle = 0;
    bool bound = false;
  };
}