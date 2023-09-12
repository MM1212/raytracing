#include <engine.hpp>

int main(void)
{
  Engine::Window* window = Instance<Engine::Window>::Get();

  window->addLayer<Engine::Layers::DemoLayer>();

  if (!window->init({ 1280, 720 }, "Hello World"))
    return 1;
  window->run();
  return 0;
}