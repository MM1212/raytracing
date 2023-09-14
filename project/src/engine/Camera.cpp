#include "engine/Camera.hpp"
#include <engine/engine.hpp>

using Engine::Camera;

static constexpr glm::vec3 upDirection = glm::vec3{ 0.0f, 1.0f, 0.0f };


Camera::Camera(
  Settings settings,
  glm::vec3 position,
  glm::vec3 direction
) : settings(settings), position(position), direction(direction) {}

void Camera::onUpdate(float deltaTime) {
  glm::vec2 mousePos = Engine::Input::GetMousePosition();
  glm::vec2 mouseDelta = (mousePos - this->lastMousePos) * 0.002f;
  this->lastMousePos = mousePos;

  if (Input::IsMouseButtonDown(Input::MouseButton::Right)) {
    Input::SetCursorMode(Input::CursorMode::Normal);
    return;
  }

  Input::SetCursorMode(Input::CursorMode::Locked);

  bool moved = false;

  glm::vec3 rightDirection = glm::cross(this->direction, upDirection);

  if (Input::IsKeyDown(Input::KeyCode::W)) {
    this->position += this->direction * this->getSpeed() * deltaTime;
    moved = true;
  }
  if (Input::IsKeyDown(Input::KeyCode::S)) {
    this->position -= this->direction * this->getSpeed() * deltaTime;
    moved = true;
  }
  if (Input::IsKeyDown(Input::KeyCode::A)) {
    this->position -= rightDirection * this->getSpeed() * deltaTime;
    moved = true;
  }
  if (Input::IsKeyDown(Input::KeyCode::D)) {
    this->position += rightDirection * this->getSpeed() * deltaTime;
    moved = true;
  }
  if (Input::IsKeyDown(Input::KeyCode::Q)) {
    this->position -= upDirection * this->getSpeed() * deltaTime;
    moved = true;
  }
  if (Input::IsKeyDown(Input::KeyCode::E)) {
    this->position += upDirection * this->getSpeed() * deltaTime;
    moved = true;
  }

  if (mouseDelta.x != 0.0f || mouseDelta.y != 0.0f) {
    float pitchDelta = mouseDelta.y * this->getRotationSpeed();
    float yawDelta = mouseDelta.x * this->getRotationSpeed();

    glm::quat quaternion = glm::normalize(
      glm::cross(
        glm::angleAxis(-pitchDelta, rightDirection),
        glm::angleAxis(-yawDelta, upDirection)
      )
    );
    this->direction = glm::rotate(quaternion, this->direction);
    moved = true;
  }
  if (!moved)
    return;
  this->recalculateView();
  this->recalculateRayDirections();
}

void Camera::onResize(glm::uvec2 size) {
  this->viewport = size;
  this->settings.aspectRatio = static_cast<float>(size.x) / static_cast<float>(size.y);
  this->recalculateProjection();
  this->recalculateRayDirections();
}

void Camera::recalculateProjection() {
  this->projection = glm::perspective(
    glm::radians(this->settings.verticalFov),
    this->settings.aspectRatio,
    this->settings.nearClip,
    this->settings.farClip
  );
  this->inverseProjection = glm::inverse(this->projection);
}

void Camera::recalculateView() {
  this->view = glm::translate(glm::mat4(1.0f), this->position);
  this->view = glm::lookAt(
    this->position,
    this->position + this->direction,
    upDirection
  );
  this->inverseView = glm::inverse(this->view);
}

void Camera::recalculateRayDirections() {
  this->cachedRayDirections.resize(this->viewport.x * this->viewport.y);
  for (uint32_t y = 0; y < this->viewport.y; y++) {
    for (uint32_t x = 0; x < this->viewport.x; x++) {
      glm::vec2 coord = glm::vec2{ x / static_cast<float>(this->viewport.x), y / static_cast<float>(this->viewport.y) };
      coord = (coord * 2.0f) - 1.0f;
      glm::vec4 rayClip = glm::vec4{ coord.x, coord.y, 1.0f, 1.0f };
      glm::vec4 rayEye = this->inverseProjection * rayClip;
      glm::vec3 rayDirection = glm::vec3(
        this->inverseView *
        glm::vec4(glm::normalize(glm::vec3(rayEye) / rayEye.w), 0)
      );
      this->cachedRayDirections[x + y * this->viewport.x] = rayDirection;
    }
  }
}