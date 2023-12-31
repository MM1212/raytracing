#include "engine/engine.hpp"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glm/gtc/type_ptr.hpp>
#include <cstdio>
#include <algorithm>

static void glfw_error_callback(int error, const char* description)
{
  std::fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

static void glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  auto* win = reinterpret_cast<Engine::Window*>(glfwGetWindowUserPointer(window));
  win->onResize(width, height);
}

using Engine::Window;


Window::Window(glm::ivec2 size, std::string_view title, bool vSync) {
  this->init(size, title, vSync);
}

Window::~Window() {
  this->destroy();
}

bool Window::destroy() {
  if (!this->initialized())
    return false;
  for (auto& layer : this->layers) {
    layer->onDetach();
  }
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwDestroyWindow(this->window);
  this->window = nullptr;
  glfwTerminate();
  this->layers.clear();
  return true;
}

bool Window::init(glm::ivec2 size, std::string_view title, bool vSync) {
  if (this->initialized())
    return false;
  this->size = size;
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit())
    return false;
  this->window = glfwCreateWindow(size.x, size.y, title.data(), nullptr, nullptr);
  if (!this->window) {
    glfwTerminate();
    return false;
  }
  glfwMakeContextCurrent(this->window);
  glfwSwapInterval(vSync); // Enable vsync

  // IMGUI SETUP
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();

  ImGuiStyle& style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(this->window, true);
  ImGui_ImplOpenGL3_Init(nullptr);

  glfwSetWindowUserPointer(this->window, this);
  glfwSetFramebufferSizeCallback(this->window, glfw_framebuffer_size_callback);

  return true;
}

bool Window::removeLayer(uint32_t idx) {
  const auto it = std::find_if(this->layers.begin(), this->layers.end(), [idx](const auto& layer) {
    return layer->id == idx;
    });
  if (it == this->layers.end())
    return false;
  this->layers.erase(it);
  return true;
}

void Window::onResize(int width, int height) {
  this->size = { width, height };
  for (auto layer : this->layers) {
    layer->onResize(this->size);
  }
}

void Window::run() {
  if (this->running)
    return;
  this->running = true;
  const auto& io = ImGui::GetIO();
  while (this->running && !glfwWindowShouldClose(this->window)) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    for (auto layer : this->layers) {
      if (layer->firstUpdate) {
        layer->onAttach(*this);
        layer->firstUpdate = false;
      }
      layer->onUpdate(this->deltaTime);
    }
    ImGui::Render();
    glm::ivec2 frameBuffer;
    glfwGetFramebufferSize(this->window, &frameBuffer.x, &frameBuffer.y);
    glViewport(0, 0, frameBuffer.x, frameBuffer.y);
    for (auto layer : this->layers) {
      layer->onRender();
    }
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      GLFWwindow* backup_current_context = glfwGetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      glfwMakeContextCurrent(backup_current_context);
    }

    glfwSwapBuffers(this->window);
    const float time = static_cast<float>(glfwGetTime());
    this->frameTime = time - this->lastFrameTime;
    this->deltaTime = glm::min<float>(this->frameTime, 0.0333f);
    this->lastFrameTime = time;
  }
  this->destroy();
}