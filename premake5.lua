workspace "Renderer"
	architecture "x64"
	startproject "Renderer"

	configurations{ "Debug", "Release" }

	--system { "windows", "linux"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "Renderer/vendor/GLFW"
	include "Renderer/vendor/GLAD"
group ""

project "Renderer"
	location "Renderer"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.location}/src/**.h",
		"%{prj.location}/src/**.cpp",
		"%{prj.location}/src/**.c",
		"%{prj.location}/src/**.hpp"
	}

	includedirs
	{
		"%{prj.location}/src",
		"%{prj.location}/src/vendor",
		"Renderer/vendor/GLFW/include",
		"Renderer/vendor/GLAD/include"
	}

	links
	{
		"GLFW",
		"GLAD"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"_CRT_SECURE_NO_WARNINGS",
			"GLFW_INCLUDE_NONE"
		}

		links{"opengl32.lib", "User32.lib", "Gdi32.lib" ,"Shell32.lib"}

	filter "system:linux"
		systemversion "latest"

		defines
		{
			"_GLFW_X11"
		}

		links{"X11", "GL", "GLU"}

	configuration { "linux", "gmake" }
		linkoptions { "-lglfw3 -lrt -lXrandr -lXinerama -lXi -lXcursor -lGL -lm -ldl -lXrender -ldrm -lXdamage -lX11-xcb -lxcb-glx -lxcb-dri2 -lxcb-dri3 -lxcb-present -lxcb-sync -lxshmfence -lXxf86vm -lXfixes -lXext -lX11 -lpthread -lxcb -lXau -lXdmcp" }

