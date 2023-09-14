#pragma once

#include <cstdint>
#include <glm/glm.hpp>

namespace Engine {
  class Window;

  class Layer {
  public:
    virtual void onAttach(const Window& win) {}
    virtual void onDetach() {}
    virtual void onUpdate(float deltaTime) {}
    virtual void onRender() {}
    virtual void onResize(glm::uvec2 size) {}
    virtual ~Layer() {}
    Layer() {}
    Layer(uint32_t idx) {}
    Layer(uint32_t idx, int priority) {}
  private:
    uint32_t id = -1;
    int priority = -1;
    bool firstUpdate = true;

    friend class Window;
  };
}