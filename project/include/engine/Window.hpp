#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <string_view>
#include <memory>
#include <utils/Instance.hpp>
#include <cstdint>

#include "render/Layer.hpp"

namespace Engine {
  class Window {
  public:
    Window(glm::ivec2 size, std::string_view title, bool vSync = true);
    ~Window();
    Window() = default;

    inline bool initialized() const { return this->window != nullptr; }
    inline bool isRunning() const { return this->running; }
    inline GLFWwindow* getWindow() const { return this->window; }
    inline glm::vec2 getSize() const { return this->size; }
    template <typename T, typename ...Args>
    uint32_t addLayer(Args&&... args) {
      const uint32_t idx = this->layerIdx++;
      this->layers.emplace_back(std::make_shared<T>(idx, std::forward<Args>(args)...));
      return idx;
    }
    bool removeLayer(uint32_t idx);
    bool init(glm::ivec2 size, std::string_view title, bool vSync = true);
    void run();
    bool destroy();
  private:
    GLFWwindow* window = nullptr;
    glm::ivec2 size;
    std::vector<std::shared_ptr<Layer>> layers;
    uint32_t layerIdx = 0;
    bool running = false;
    float deltaTime = 0.0f;
    float frameTime = 0.0f;
    float lastFrameTime = 0.0f;

  };
}