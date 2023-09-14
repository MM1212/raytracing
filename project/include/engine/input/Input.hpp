#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include "keycodes.hpp"

namespace Engine {
  namespace Input {
    bool IsKeyDown(KeyCode keycode);
    bool IsMouseButtonDown(MouseButton button);

    glm::vec2 GetMousePosition();

    void SetCursorMode(CursorMode mode);
  }
}
