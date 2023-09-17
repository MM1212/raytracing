#include <engine/entity/Entity.hpp>
#include "engine/entity/components/shapes/Sphere.hpp"
#include <engine/Ray.hpp>

using namespace Engine;
using Components::SphereShape;

float SphereShape::computeIntersection(const Transform& transform, const Ray& ray) const {
  const glm::vec3& center = transform.position;
  const float radius = transform.scale.x;

  glm::vec3 originDelta = ray.origin - center;

  // quadratic equation
  float a = glm::dot(ray.direction, ray.direction);
  float b = 2.0f * glm::dot(ray.direction, originDelta);
  float c = glm::dot(originDelta, originDelta) - radius * radius;

  // discriminant
  // if discriminant is negative, there are no real roots
  // if discriminant is zero, there is one real root
  // if discriminant is positive, there are two real roots
  // b^2 - 4ac
  float discriminant = b * b - 4.0f * a * c;
  if (discriminant < 0.0f)
    return -1.0f;

  // if discriminant is zero, there is one real root
  float t0 = (-b - glm::sqrt(discriminant)) / (2.0f * a);
  float t1 = (-b + glm::sqrt(discriminant)) / (2.0f * a);
  float dist = std::min(t0, t1);
  if (dist < 0.0f)
    dist = std::max(t0, t1);
  if (dist <= 0.0f)
    return -1.0f;
  return dist;
}

RayResult SphereShape::computeRayResult(const Entity entity, float distance, const Ray& ray) const {
  const auto& transform = entity.getComponent<Transform>();
  const glm::vec3& center = transform.position;

  glm::vec3 endCoords = ray.origin + ray.direction * distance;
  glm::vec3 normal = glm::normalize(endCoords - center);

  return RayResult{ true, endCoords, normal, distance, entity };
}