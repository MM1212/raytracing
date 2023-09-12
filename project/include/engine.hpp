#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <string_view>
#include <memory>
#include <utils/Instance.hpp>


namespace Engine {

  class Window;

  class Layer {
  public:
    virtual void onAttach() {};
    virtual void onDetach() {};
    virtual void onUpdate() {};
    virtual void onRender() {};
  protected:
    Layer(uint32_t idx) : id(idx) {};
    Layer(uint32_t idx, int priority) : id(idx), priority(priority) {};
    virtual ~Layer() { this->onDetach(); };
  private:
    uint32_t id = -1;
    int priority = -1;
    bool firstUpdate = true;

    friend class Window;
  };

  class Window {
  public:
    inline bool initialized() const { return this->window != nullptr; }
    inline bool isRunning() const { return this->running; }
    inline GLFWwindow* getWindow() const { return this->window; }
    inline glm::vec2 getSize() const { return this->size; }
    template <typename T, typename ...Args>
    uint32_t addLayer(Args... args) {
      const uint32_t idx = this->layerIdx++;
      this->layers.emplace_back(std::move(std::make_shared<T>(idx, args...)));
      return idx;
    }
    bool removeLayer(uint32_t idx);
    bool init(glm::vec2 size, std::string_view title, bool vSync = true);
    void run();
    bool destroy();
  private:
    GLFWwindow* window = nullptr;
    glm::vec2 size;
    std::vector<std::shared_ptr<Layer>> layers;
    uint32_t layerIdx = 0;
    bool running = false;

  private:
    Window(glm::vec2 size, std::string_view title, bool vSync = true);
    ~Window();
    Window() = default;

    friend class Instance<Window>;
  };


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