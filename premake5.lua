workspace "TEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

startproject "Sandbox" 

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include Table that has our relevant paths
IncludeDir = {}
IncludeDir["GLFW"] = "TEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "TEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "TEngine/vendor/imgui"
IncludeDir["glm"] = "TEngine/vendor/glm" 
IncludeDir["stb_image"] = "TEngine/vendor/stb_image" 

-- Includes the premake file found in the GLFW folder, so we can call it from here --
include "TEngine/vendor/GLFW" 
include "TEngine/vendor/Glad"  
include "TEngine/vendor/imgui"  

project "TEngine"
	location "TEngine"
	kind "StaticLib" 
	language "C++"
	cppdialect "C++20" 
	staticruntime "on"  
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")   

	pchheader "tepch.h"
	pchsource "TEngine/src/tepch.cpp" 

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp", 
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/stb_image/**.cpp", 
		"%{prj.name}/vendor/stb_image/**.h" 
	}

	includedirs 
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib" 
	}

	filter "system:windows"
		systemversion "10.0.19041.0:latest"

		defines
		{
			"TE_PLATFORM_WINDOWS",
			"TE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		buildoptions 
		{
			"/utf-8"
		}

	filter "configurations:Debug"
		defines "TE_DEBUG"
		runtime "Debug" 
		symbols "on"

	filter "configurations:Release"
		defines "TE_RELEASE" 
		runtime "Release"
		optimize "on" 

	filter "configurations:Dist"
		defines "TE_DIST" 
		runtime "Release"
		optimize "on" 


project "Sandbox"

	location "Sandbox"
	kind "ConsoleApp" 
	language "C++"
	cppdialect "C++20"
	staticruntime "on"  

	targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")   

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs 
	{
		"TEngine/vendor/spdlog/include",
		"TEngine/src",
		"TEngine/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"TEngine" 
	}

	filter "system:windows"
		systemversion "10.0.19041.0:latest"

		defines
		{
			"TE_PLATFORM_WINDOWS"
		}

		buildoptions 
		{
			"/utf-8"
		}

	filter "configurations:Debug"
		defines "TE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "TE_RELEASE" 
		runtime "Release"
		optimize "on" 

	filter "configurations:Dist"
		defines "TE_DIST" 
		runtime "Release"
		optimize "on" 