#include "Application.hpp"
#include <engine/Renderer.hpp>
#include <engine/render/Layers.hpp>

using namespace RayTracing;

void AppLayer::onAttach(const Engine::Window&) {
  this->getApp()->onAttach();
}
void AppLayer::onDetach() {
  this->getApp()->onDetach();
}
void AppLayer::onUpdate(float deltaTime) {
  this->getApp()->onUpdate(deltaTime);
}
void AppLayer::onRender() {
  this->getApp()->onRender();
}
void AppLayer::onResize(glm::uvec2 size) {
  this->getApp()->onResize(size);
}

Application* AppLayer::getApp() const {
  return Instance<Application>::Get();
}

Application::Application()
  : window(std::make_unique<Engine::Window>()), scene(std::make_shared<Engine::Scene>()) {}

void Application::setup(glm::uvec2 size, std::string_view title) {
  if (!this->window->init(size, title, true))
    return;
  this->window->addLayer<AppLayer>();
  // this->window->addLayer<Engine::Layers::DemoLayer>();
  {
    Engine::Entity sphere = this->scene->newEntity("sphere");
    if (sphere) {
      sphere.getComponent<Engine::Components::Transform>().scale.x = 0.5f;
      sphere.getPosition().z = -5.0f;
      sphere.getPosition().x = -1.0f;
      sphere.addComponent<Engine::Components::SphereShape>();
      auto& mat = sphere.addComponent<Engine::Components::Material>();
      mat.albedo = glm::vec3{ 1.0f, 0.0f, 0.0f };
      mat.emissionColor = glm::vec3{ 1.0f };
      mat.emissionStrength = 1.0f;
      mat.roughness = 0.0f;
    }
  }
  {
    Engine::Entity sphere = this->scene->newEntity("sphere2");
    if (sphere) {
      sphere.getComponent<Engine::Components::Transform>().scale.x = 0.5f;
      sphere.getPosition().z = -5.0f;
      sphere.getPosition().x = 1.0f;
      sphere.addComponent<Engine::Components::SphereShape>();
      auto& mat = sphere.addComponent<Engine::Components::Material>();
      mat.albedo = glm::vec3{ 1.0f, 0.0f, 0.0f };
      mat.roughness = 1.0f;
    }
  }
  this->window->run();
}

void Application::onAttach() {
  this->scene->onResize(this->window->getSize());
  Instance<Engine::Renderer>::Get()->onResize(this->window->getSize());
}
void Application::onDetach() {}
void Application::onUpdate(float deltaTime) {
  (void)deltaTime;
  this->scene->onUpdate(deltaTime);
}

void Application::onRender() {
  Engine::Renderer* renderer = Instance<Engine::Renderer>::Get();
  renderer->beginScene(this->scene.get(), this->window->getSize());
  renderer->render();
  renderer->endScene();
}

void Application::onResize(glm::uvec2 size) {
  this->scene->onResize(size);
  Instance<Engine::Renderer>::Get()->onResize(size);
}