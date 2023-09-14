local imgui = vendorFiles("imgui");

project "RayTracing"
  kind "ConsoleApp"
  language "C++"
  targetname "raytracing"
  cppdialect "C++20"
  targetdir "bin/%{cfg.buildcfg}"
  staticruntime "off"
  stl "libc++"
  toolset "clang"

  files {
    imgui "backends/imgui_impl_glfw.h",
    imgui "backends/imgui_impl_opengl3.h",
    imgui "backends/imgui_impl_glfw.cpp",
    imgui "backends/imgui_impl_opengl3.cpp",
    "src/**.cpp"
  }

  includedirs {
    "include",
    imgui(),
    vendorFiles("glfw/include")(),
    vendorFiles("glm")(),
    vendorFiles("entt/src")()
  }

  links {
    "GL",
    "GLFW",
    "ImGui",
  }

  targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
  objdir ("../objs/" .. outputdir .. "/%{prj.name}")

  filter "configurations:debug"
    defines { "WL_DEBUG" }
    runtime "Debug"
    symbols "On"

  filter "configurations:release"
    defines { "WL_RELEASE" }
    runtime "Release"
    optimize "On"
    symbols "On"