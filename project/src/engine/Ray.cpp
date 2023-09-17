#include "engine/Ray.hpp"
#include <engine/entity/Entity.hpp>

namespace Engine {
  RayResult RayResult::NoHit() {
    return { false, glm::vec3(0.0f), glm::vec3(0.0f), 0.0f, Entity{} };
  }
}