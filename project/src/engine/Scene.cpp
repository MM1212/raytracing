#include <engine/entity/Entity.hpp>
#include <engine/Renderer.hpp>
#include "engine/Scene.hpp"

using Engine::Scene;

void Scene::onUpdate(float deltaTime) {
  this->viewportCam.onUpdate(deltaTime);
}

void Scene::onResize(glm::uvec2 size) {
  this->viewportCam.onResize(size);
}

Engine::Entity Scene::newEntity(const std::string_view tag) {
  return this->newEntity(UUID(), tag);
}

Engine::Entity Scene::newEntity(const UUID id, const std::string_view name) {
  Entity entity = Entity(this->registry.create(), this);
  entity.addComponent<Components::ID>(id);
  entity.addComponent<Components::Transform>();
  entity.addComponent<Components::Tag>(name.empty() ? "Entity" : name);
  this->entities.try_emplace(entity.getId(), entity.getHandle());
  return entity;
}

Engine::Entity Scene::getEntity(UUID id) const {
  if (this->entities.find(id) == this->entities.end())
    return {};
  return Entity(this->entities.at(id), const_cast<Scene*>(this));
}

Engine::Entity Scene::getEntity(const std::string_view tag) const {
  auto view = this->view<Components::Tag>();
  for (auto handle : view) {
    if (view.get<Components::Tag>(handle).name == tag)
      return Entity(handle, const_cast<Scene*>(this));
  }
  return {};
}

bool Scene::hasEntity(UUID id) const {
  return this->entities.find(id) != this->entities.end();
}

bool Scene::removeEntity(Entity entity) {
  if (!this->hasEntity(entity))
    return false;
  this->registry.destroy(entity);
  return true;
}