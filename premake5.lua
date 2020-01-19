workspace "Renderer"
	architecture "x64"
	startproject "Renderer"

	configurations{ "Debug", "Release" }

	flags{ "MultiProcessorCompile" }
	--system { "windows", "linux"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "Renderer/vendor/GLFW"
	include "Renderer/vendor/GLAD"
group ""

project "Renderer"
	location "Renderer"
	kind "StaticLib"
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
			"GLFW_INCLUDE_NONE",
			"RENDER_PLATFORM_WINDOWS_"
		}

		links{"opengl32.lib"}

	filter "system:linux"
		systemversion "latest"

		defines
		{
			"_GLFW_X11",
			"RENDER_PLATFORM_LINUX_"
		}

		links{"X11", "GL", "GLU"}

	configuration { "linux", "gmake" }
		linkoptions { "-lglfw3 -lrt -lXrandr -lXinerama -lXi -lXcursor -lGL -lm -ldl -lXrender -ldrm -lXdamage -lX11-xcb -lxcb-glx -lxcb-dri2 -lxcb-dri3 -lxcb-present -lxcb-sync -lxshmfence -lXxf86vm -lXfixes -lXext -lX11 -lpthread -lxcb -lXau -lXdmcp" }

project "Sandbox"
		location "Sandbox"
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
			"Renderer/src",
			"Renderer/src/vendor",
			"Renderer/vendor/GLFW/include",
			"Renderer/vendor/GLAD/include"
		}
	
		links
		{
			"Renderer"
		}
	
		filter "system:windows"
			systemversion "latest"
	
		filter "system:linux"
			systemversion "latest"