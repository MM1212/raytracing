#pragma once

#include "entity/Entity.hpp"
#include <glm/glm.hpp>

namespace Engine {
  struct Ray {
    bool hit;
    glm::vec3 endCoords;
    glm::vec3 normal;
    Entity target;
  };
}