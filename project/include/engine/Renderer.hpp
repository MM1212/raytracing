#pragma once

#include <engine/Ray.hpp>
#include <engine/Scene.hpp>
#include <utils/Instance.hpp>
#include <memory>
#include <glm/glm.hpp>

#include "Image.hpp"

namespace Engine {
  class Renderer {
  public:
    ~Renderer() = default;
    void beginScene(const Scene* scene, glm::ivec2 size);
    void endScene();
    void render();
    void onResize(glm::ivec2 size);
  private:
    RayResult traceEntities(const Ray& ray);
    glm::vec3 traceRay(Ray& ray, uint32_t bounces, uint32_t& seed);
    glm::vec3 getEnvironmentLight(const Ray& ray);
    const Scene* scene;
    std::shared_ptr<Image> image = nullptr;
  };
}