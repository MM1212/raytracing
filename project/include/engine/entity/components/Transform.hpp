#pragma once

#include <glm/glm.hpp>

namespace Engine {
  namespace Components {
    struct Transform {
      glm::vec3 position{ 0.0f };
      glm::vec3 rotation{ 0.0f };
      glm::vec3 scale{ 1.0f };

      Transform() = default;
      Transform(const Transform&) = default;
      Transform(glm::vec3 position)
        : position(position) {}
      Transform(glm::vec3 position, glm::vec3 rotation)
        : position(position), rotation(rotation) {}
      Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
        : position(position), rotation(rotation), scale(scale) {}
    };
  }
}