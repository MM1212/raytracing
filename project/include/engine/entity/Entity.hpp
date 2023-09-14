#pragma once

#include <entt/entt.hpp>

#include "components/all.hpp"

#include "engine/Scene.hpp"

namespace Engine {
  class Entity {
  public:
    Entity() = default;
    Entity(entt::entity handle, Scene* scene)
      : handle(handle), scene(scene) {}
    ~Entity() = default;
    entt::entity getHandle() const { return this->handle; }
    const Scene* getScene() const { return this->scene; }
    void setHandle(entt::entity handle) { this->handle = handle; }
    void setScene(Scene* scene) { this->scene = scene; }

    template <typename T, typename ...Args>
    T& addComponent(Args&&... args) {
      return this->getRegistry().emplace<T>(this->handle, std::forward<Args>(args)...);
    }
    template <typename T>
    const T& getComponent() const {
      if (!this->hasComponent<T>())
        throw std::runtime_error("Entity does not have component");
      return this->getRegistry().get<T>(this->handle);
    }
    template <typename T>
    T& getComponent() {
      if (!this->hasComponent<T>())
        throw std::runtime_error("Entity does not have component");
      return this->getRegistry().get<T>(this->handle);
    }
    template <typename ...T>
    bool hasComponent() const {
      return this->getRegistry().any_of<T...>(this->handle);
    }
    template <typename T, typename ...U>
    bool removeComponent() {
      if (!this->hasComponent<T>())
        return false;
      return this->getRegistry().remove<T, U...>(this->handle) > 0;
    }
    /* component shortcuts */
    auto getId() const { return this->getComponent<Components::ID>().id; }
    const std::string_view getName() const { return this->getComponent<Components::Tag>().name; }

    operator entt::entity() const { return this->handle; }
    operator const UUID() const { return this->getId(); }
    operator const std::string_view() const { return this->getName(); }
    operator bool() const { return this->handle != entt::null; }
  private:
    entt::registry& getRegistry() { return this->scene->getRegistry(); }
    const entt::registry& getRegistry() const { return this->scene->getRegistry(); }
  private:
    entt::entity handle{ entt::null };
    Scene* scene = nullptr;
  };
}