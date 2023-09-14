#pragma once

#include <glm/glm.hpp>
#include <engine/engine.hpp>

namespace Engine {
  namespace Layers {
    class DemoLayer : public Layer {
    private:
      glm::vec4 clear_color = { 0.45f, 0.55f, 0.60f, 1.00f };
    public:
      DemoLayer(uint32_t idx) : Layer(idx) {};
      ~DemoLayer() = default;
      void onAttach();
      void onDetach();
      void onUpdate();
      void onRender();
    };
  }
}