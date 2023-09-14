#pragma once

#include <engine/Scene.hpp>
#include <utils/Instance.hpp>

namespace Engine {
  class Renderer {
  public:
    void render(const Scene* scene);
  private:
    const Scene* scene;
  };
}