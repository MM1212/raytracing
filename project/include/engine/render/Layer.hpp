#pragma once

#include <cstdint>
#include <glm/glm.hpp>

namespace Engine {
  class Window;

  class Layer {
  public:
    virtual void onAttach(const Window&) = 0;
    virtual void onDetach() = 0;
    virtual void onUpdate(float) = 0;
    virtual void onRender() = 0;
    virtual void onResize(glm::uvec2) = 0;
    virtual ~Layer() = default;
    Layer() = default;
    Layer(uint32_t idx) : id(idx) {}
    Layer(uint32_t idx, int priority) : id(idx), priority(priority) {}
  private:
    uint32_t id = -1;
    int priority = -1;
    bool firstUpdate = true;

    friend class Window;
  };
}