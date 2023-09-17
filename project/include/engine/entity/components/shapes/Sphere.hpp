#pragma once

#include <glm/glm.hpp>

#include "Base.hpp"

namespace Engine {
  namespace Components {
    struct SphereShape : public Shape {
      SphereShape() : Shape{ Type::Sphere } {}
      float computeIntersection(const Transform& transform, const Ray& ray) const override;
      RayResult computeRayResult(const Entity entity, float distance, const Ray& ray) const override;
    };
  }
}