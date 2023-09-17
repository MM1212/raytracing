#include <engine/engine.hpp>
#include "engine/render/Layers.hpp"
#include <iostream>
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

using Engine::Layers::DemoLayer;

void DemoLayer::onAttach(const Window&) {
  std::cout << "DemoLayer attached" << std::endl;
}

void DemoLayer::onDetach() {
  std::cout << "DemoLayer detached" << std::endl;
}

void DemoLayer::onUpdate(float) {
  // Our state
  static bool show_demo_window = true;
  static bool show_another_window = false;
  static auto& io = ImGui::GetIO();

  // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
  if (show_demo_window)
    ImGui::ShowDemoWindow(&show_demo_window);

  // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
  {
    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
    ImGui::Checkbox("Another Window", &show_another_window);

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3("clear color", glm::value_ptr(this->clear_color)); // Edit 3 floats representing a color

    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
      counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();
  }

  // 3. Show another simple window.
  if (show_another_window)
  {
    ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
    ImGui::Text("Hello from another window!");
    if (ImGui::Button("Close Me"))
      show_another_window = false;
    ImGui::End();
  }

}

void DemoLayer::onRender() {
  glClearColor(this->clear_color.r, this->clear_color.g, this->clear_color.b, this->clear_color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

void DemoLayer::onResize(glm::uvec2 size) {
  glViewport(0, 0, size.x, size.y);
}