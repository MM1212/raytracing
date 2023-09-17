#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace Random {
  template <typename T>
  T Value(uint32_t& seed) {
    seed = seed * 747796405 + 2891336453;
    T result = ((seed >> ((seed >> 28) + 4)) ^ seed) * 277803737;
    return result;
  }
  template <>
  float Value(uint32_t& seed) {
    return Value<uint64_t>(seed) / static_cast<float>(UINT32_MAX);
  }
  template <>
  glm::vec3 Value(uint32_t& seed) {
    return glm::vec3(Value<float>(seed), Value<float>(seed), Value<float>(seed));
  }

  template <typename T>
  T NormalDistribution(uint32_t& seed) {
    T theta = 2 * glm::pi<T>() * Value<T>(seed);
    T rho = glm::sqrt(-2 * glm::log(Value<T>(seed)));
    return rho * glm::cos(theta); 
  }
  template <>
  glm::vec3 NormalDistribution(uint32_t& seed) {
    return glm::vec3(NormalDistribution<float>(seed), NormalDistribution<float>(seed), NormalDistribution<float>(seed));
  }

  glm::vec3 InUnitSphere(uint32_t& seed) {
    return glm::normalize(NormalDistribution<glm::vec3>(seed) * 2.0f - 1.0f);
  }
};