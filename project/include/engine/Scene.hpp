#pragma once

#include <vector>

namespace Engine { class Entity; }

#include "Camera.hpp"
#include <utils/UUID.hpp>

#include <entt/entt.hpp>
#include <unordered_map>

namespace Engine {
  class Scene {
  public:
    Scene() = default;
    ~Scene() = default;

    const auto& getEntities() const { return this->entities; }
    auto& getEntities() { return this->entities; }
    entt::registry& getRegistry() { return this->registry; };
    const entt::registry& getRegistry() const { return this->registry; };

    void onUpdate(float deltaTime);
    void submitToRender();
    void onResize(glm::uvec2 size);

    Entity newEntity(const std::string_view tag);
    Entity newEntity(const UUID id, const std::string_view tag);
    Entity getEntity(UUID id) const;
    Entity getEntity(const std::string_view tag) const;
    bool hasEntity(UUID id) const;
    bool removeEntity(Entity entity);

    template <typename... Components>
    auto view() const { return this->registry.view<Components...>(); }

  private:
    entt::registry registry;
    std::unordered_map<UUID, entt::entity> entities;
    Camera viewportCam;
    friend class Entity;
  };
}