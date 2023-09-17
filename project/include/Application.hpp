#pragma once

#include <engine/engine.hpp>
#include <utils/Instance.hpp>
#include <memory>

namespace RayTracing {
  class Application;
  class AppLayer : public Engine::Layer {
  public:
    AppLayer() = default;
    AppLayer(uint32_t idx) : Layer(idx) {}
    ~AppLayer() = default;

    void onAttach(const Engine::Window& win) override;
    void onDetach() override;
    void onUpdate(float deltaTime) override;
    void onRender() override;
    void onResize(glm::uvec2 size) override;

  private:
    Application* getApp() const;
  };
  class Application {
  public:
    void setup(glm::uvec2 size, std::string_view title);

    const auto& getScene() const { return this->scene; }
    auto& getScene() { return this->scene; }
    const auto& getWindow() const { return this->window; }
    auto& getWindow() { return this->window; }
  private:
    std::unique_ptr<Engine::Window> window;
    std::shared_ptr<Engine::Scene> scene;
    Application();
    ~Application() = default;

    // will be bound to the app's window layer
    void onAttach();
    void onDetach();
    void onUpdate(float deltaTime);
    void onResize(glm::uvec2 size);
    void onRender();

    friend class AppLayer;
    friend class ::Instance<Application>;
  };
}