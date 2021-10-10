workspace "Renderer"
	architecture "x64"
	startproject "Renderer"

	configurations{ "Debug", "Release" }

	flags{ "MultiProcessorCompile" }

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
		"%{prj.location}/vendor/slogger/**.h",
		"%{prj.location}/vendor/slogger/**.cpp",
		"%{prj.location}/vendor/stb_image/**.h",
		"%{prj.location}/vendor/stb_image/**.cpp",
		"%{prj.location}/vendor/glm/**.hpp",
		"%{prj.location}/vendor/glm/**.inl",
		
		"%{prj.location}/src/**.h",
		"%{prj.location}/src/**.cpp",
		"%{prj.location}/src/**.c",
		"%{prj.location}/src/**.hpp"
	}

	includedirs
	{
		"%{prj.location}/src",
		"%{prj.location}/vendor",
		"%{prj.location}/vendor/GLFW/include",
		"%{prj.location}/vendor/GLAD/include"
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
			"Renderer/vendor"
		}
	
		links
		{
			"Renderer",
			"GLFW",
			"GLAD"
		}

		configuration { "linux", "gmake" }
			linkoptions {"-lX11 -lpthread -ldl"}

		filter "system:windows"
			systemversion "latest"
	
		filter "system:linux"
			systemversion "latest"
