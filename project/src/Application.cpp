#include "Application.hpp"

using namespace RayTracing;

void AppLayer::onAttach(const Engine::Window& win) {
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
  : window(std::make_unique<Engine::Window>()) {}

void Application::setup(glm::uvec2 size, std::string_view title) {
  if (!this->window->init(size, title, true))
    return;
  this->window->addLayer<AppLayer>();
  this->window->run();
}

void Application::onAttach() {}
void Application::onDetach() {}
void Application::onUpdate(float deltaTime) {
  this->scene->onUpdate(deltaTime);
}

void Application::onRender() {
  this->scene->submitToRender();
}

void Application::onResize(glm::uvec2 size) {
  this->scene->onResize(size);
}