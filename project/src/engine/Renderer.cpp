#include "engine/Renderer.hpp"
#include <engine/entity/components/all.hpp>
#include <utils/Random.hpp>
#include <iostream>

using namespace Engine;

void Renderer::beginScene(const Scene* scene, glm::ivec2 size) {
  this->scene = scene;
  if (!this->image)
    this->image = std::make_shared<Image>(size);
}

void Renderer::endScene() {
  this->scene = nullptr;
}

static uint32_t ConvertToRGBA(const glm::vec4& color)
{
  uint8_t r = (uint8_t)(color.r * 255.0f);
  uint8_t g = (uint8_t)(color.g * 255.0f);
  uint8_t b = (uint8_t)(color.b * 255.0f);
  uint8_t a = (uint8_t)(color.a * 255.0f);

  uint32_t result = (a << 24) | (b << 16) | (g << 8) | r;
  return result;
}

void Renderer::render() {
  if (!this->scene)
    return;
  auto size = this->image->getSize();
  auto& camera = this->scene->getViewportCamera();
  for (int y = 0; y < size.y; y++) {
    for (int x = 0; x < size.x; x++) {
      uint32_t seed = x + y * size.x;
      Ray ray;
      ray.origin = camera.getPosition();
      ray.direction = camera.getCachedRayDirection(x, y);
      glm::vec3 color = this->traceRay(ray, 3, seed);
      this->image->setPixel(glm::ivec2{ x, y }, ConvertToRGBA(glm::vec4{ color, 1.0f }));
    }
  }
  this->image->render();
}

void Renderer::onResize(glm::ivec2 size) {
  if (!this->image)
    return;
  this->image->resize(size);
}

RayResult Renderer::traceEntities(const Ray& ray) {
  //
  auto& registry = const_cast<entt::registry&>(this->scene->getRegistry());

  // spheres
  Entity nearestEntity = Entity{};
  nearestEntity.setScene(const_cast<Scene*>(this->scene));
  Components::Shape* nearestShape = nullptr;
  float nearestDistance = 0.0f;
  {
    auto group = registry.group<Components::Transform>(entt::get<Components::SphereShape>);
    for (auto handle : group) {
      auto [transform, shape] = group.get<Components::Transform, Components::SphereShape>(handle);
      float distance = shape.computeIntersection(transform, ray);
      if (distance > 0.0f && (!nearestEntity || distance < nearestDistance)) {
        nearestEntity.setHandle(handle);
        nearestDistance = distance;
        nearestShape = &shape;
      }
    }
  }
  if (!nearestEntity)
    return RayResult::NoHit();
  return nearestShape->computeRayResult(nearestEntity, nearestDistance, ray);
}

namespace Random {
  glm::vec3 RandomHemisphere(glm::vec3& normal, uint32_t& seed) {
    glm::vec3 direction = InUnitSphere(seed);
    return direction * glm::sign(glm::dot(normal, direction));
  }
}

glm::vec3 Renderer::getEnvironmentLight(const Ray& ray) {
  constexpr glm::vec3 skyColourHorizon = glm::vec3{ 1.0f };
  constexpr glm::vec3 skyColourZenith = glm::vec3{ 0.0788092f, 0.36480793f, 0.726415f };
  constexpr glm::vec3 groundColor = glm::vec3{ 0.35f,  0.3f,  0.35f };
  constexpr uint32_t sunFocus = 500;
  constexpr uint32_t sunIntensity = 200;
  constexpr glm::vec3 sunPosition = glm::vec3{ 0.0f, 50.0f, 0.0f };

  float skyGradientT = glm::pow(glm::smoothstep(0.0f, 0.4f, ray.direction.y), 0.35f);
  glm::vec3 skyGradient = glm::mix(skyColourHorizon, skyColourZenith, skyGradientT);
  float sun = glm::pow(glm::max(0.0f, glm::dot(ray.direction, sunPosition)), sunFocus) * sunIntensity;

  float groundToSkyT = glm::smoothstep(-0.01f, 0.0f, ray.direction.y);
  float sunMask = groundToSkyT >= 1.0f;
  return glm::mix(groundColor, skyGradient, groundToSkyT) + sun * sunMask;
}

glm::vec3 Renderer::traceRay(Ray& ray, uint32_t bounces, uint32_t& seed) {
  glm::vec3 light(0.0f);
  glm::vec3 contribution(1.0f);

  for (uint32_t i = 0; i < bounces; i++) {
    RayResult result = this->traceEntities(ray);
    if (!result.hit) {
      // light += contribution * this->getEnvironmentLight(ray);
      break;
    }

    // compute lighting
    if (!result.target.hasComponent<Components::Material>())
      break;
    const auto& material = result.target.getComponent<Components::Material>();

    light += contribution * material.getEmission();
    contribution *= material.albedo;

    // compute next ray
    ray.origin = result.endCoords + result.normal * 0.0001f;
    glm::vec3 specularDirection = glm::normalize(glm::reflect(ray.direction, result.normal));
    glm::vec3 diffuseDirection = glm::normalize(result.normal + Random::InUnitSphere(seed));
    ray.direction = glm::mix(specularDirection, diffuseDirection, material.roughness);
  }

  return light;
}