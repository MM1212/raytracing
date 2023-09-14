#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>
#include <imgui.h>

namespace Engine {
  class Camera {
  public:
    struct Settings {
      float verticalFov = 45.0f;
      float aspectRatio = 1.0f;
      float nearClip = 0.1f;
      float farClip = 100.0f;
      float speed = 5.0f;
      float rotationSpeed = 0.3f;
      Settings() {}
    };
  public:
    Camera(
      Settings settings = Settings(),
      glm::vec3 position = glm::vec3{ 0.0f, 0.0f, -1.0f },
      glm::vec3 direction = glm::vec3{ 0.0f, 0.0f, 3.0f }
    );
    ~Camera() = default;

    void onUpdate(float deltaTime);
    void onResize(glm::uvec2 size);

    const glm::mat4& getProjection() const { return this->projection; };
    const glm::mat4& getView() const { return this->view; };
    const glm::mat4& getInverseView() const { return this->inverseView; };
    const glm::mat4& getInverseProjection() const { return this->inverseProjection; };

    const glm::vec3& getPosition() const { return this->position; };
    const glm::vec3& getDirection() const { return this->direction; };

    const std::vector<glm::vec3>& getCachedRayDirections() const { return this->cachedRayDirections; };

    const Settings& getSettings() const { return this->settings; };
    const glm::uvec2& getViewport() const { return this->viewport; };

    inline float getSpeed() const { return this->settings.speed; };
    inline float getRotationSpeed() const { return this->settings.rotationSpeed; };
  private:
    void recalculateProjection();
    void recalculateView();
    void recalculateRayDirections();
  private:
    glm::mat4 projection{ 1.0f };
    glm::mat4 view{ 1.0f };
    glm::mat4 inverseView{ 1.0f };
    glm::mat4 inverseProjection{ 1.0f };

    Settings settings;

    glm::vec3 position{ 0.0f };
    glm::vec3 direction{ 0.0f };

    std::vector<glm::vec3> cachedRayDirections;

    glm::uvec2 viewport{ 0 };
    glm::vec2 lastMousePos{ 0.0f };
  };
}