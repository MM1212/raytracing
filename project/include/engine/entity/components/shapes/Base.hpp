#pragma once

#include "../Transform.hpp"

namespace Engine {
  struct Ray;
  struct RayResult;
  namespace Components {
    struct Shape {
      enum class Type {
        Sphere,
        Plane
      };
      Type type;
      virtual float computeIntersection(const Transform& transform, const Ray& ray) const = 0;
      virtual RayResult computeRayResult(const Entity entity, float distance, const Ray& ray) const = 0;
      protected:
        Shape(Type type) : type(type) {}
    };
  }
}