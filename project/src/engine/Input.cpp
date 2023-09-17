#include "engine/input/Input.hpp"
#include <engine/engine.hpp>
#include <Application.hpp>

using namespace Engine;

static GLFWwindow* getWindow() {
  return Instance<RayTracing::Application>::Get()->getWindow()->getWindow();
}

bool Input::IsKeyDown(KeyCode keycode) {
  auto window = getWindow();
  auto state = glfwGetKey(window, static_cast<int>(keycode));
  return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::IsMouseButtonDown(MouseButton button) {
  auto window = getWindow();
  auto state = glfwGetMouseButton(window, static_cast<int>(button));
  return state == GLFW_PRESS;
}

glm::vec2 Input::GetMousePosition() {
  auto window = getWindow();
  double xpos, ypos = 0.0;
  glfwGetCursorPos(window, &xpos, &ypos);
  return { xpos, ypos };
}

void Input::SetCursorMode(CursorMode mode) {
  auto window = getWindow();
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL + static_cast<int>(mode));
}