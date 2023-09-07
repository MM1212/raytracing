--- https://github.com/TheCherno/imgui/blob/docking/premake5.lua

local imgui = vendorFiles("imgui");

project "ImGui"
	kind "StaticLib"
	language "C++"
  staticruntime "off"

	targetdir (path.join(rootDir, "bin/" .. outputdir .. "/%{prj.name}"))
	objdir (path.join(rootDir, "objs/" .. outputdir .. "/%{prj.name}"))

	files {
		imgui "imconfig.h",
		imgui "imgui.h",
		imgui "imgui.cpp",
		imgui "imgui_draw.cpp",
		imgui "imgui_internal.h",
		imgui "imgui_tables.cpp",
		imgui "imgui_widgets.cpp",
		imgui "imstb_rectpack.h",
		imgui "imstb_textedit.h",
		imgui "imstb_truetype.h",
		imgui "imgui_demo.cpp"
	}

	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++20"

	filter "configurations:debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:release"
		runtime "Release"
		optimize "on"
    removefiles { imgui "imgui_demo.cpp" }