workspace "TEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "TEngine"
	location "TEngine"
	kind "SharedLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")   

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp", 
	}

	includedirs 
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"  
	}

	filter "system:windows"
		cppdialect "C++20" 
		staticruntime "On" 
		systemversion "10.0.19041.0:latest"

		defines
		{
			"TE_PLATFORM_WINDOWS",
			"TE_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

		buildoptions 
		{
			"/utf-8"
		}

	filter "configurations:Debug"
		defines "TE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "TE_RELEASE" 
		optimize "On" 

	filter "configurations:Dist"
		defines "TE_DIST" 
		optimize "On" 


project "Sandbox"

	location "Sandbox"
	kind "ConsoleApp" 
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")   

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp", 
	}

	includedirs 
	{
		"TEngine/vendor/spdlog/include",
		"TEngine/src"
	}

	links
	{
		"TEngine" 
	}

	filter "system:windows"
		cppdialect "C++20" 
		staticruntime "On" 
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
		symbols "On"

	filter "configurations:Release"
		defines "TE_RELEASE" 
		optimize "On" 

	filter "configurations:Dist"
		defines "TE_DIST" 
		optimize "On" 