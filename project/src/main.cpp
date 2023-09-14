#include <Application.hpp>

int main(void)
{
  RayTracing::Application* app = Instance<RayTracing::Application>::Get();
  app->setup({ 1280, 720 }, "RayTracing");
  return 0;
}