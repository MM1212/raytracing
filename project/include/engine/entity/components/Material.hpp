#pragma once

#include <cstdint>
#include <glm/glm.hpp>

namespace Engine {
  namespace Components {
    struct Material {
      glm::vec3 albedo;
      float roughness;
      glm::vec3 emissionColor;
      float emissionStrength;

      glm::vec3 getEmission() const { return this->emissionColor * this->emissionStrength; }
    };
  }
}