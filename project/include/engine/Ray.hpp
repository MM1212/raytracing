#pragma once

#include <engine/entity/Entity.hpp>
#include <glm/glm.hpp>

namespace Engine {
  struct Ray {
    glm::vec3 origin;
    glm::vec3 direction;
  };
  struct RayResult {
    bool hit;
    glm::vec3 endCoords;
    glm::vec3 normal;
    float distance;
    Entity target;
    static RayResult NoHit();
  };
}