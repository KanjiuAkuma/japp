out_dir = "%{wks.location}/build/"
bin_dir = out_dir .. "bin/%{prj.name}/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
bin_int_dir = out_dir .. "bin-int/%{prj.name}/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

j_app = require("util/j_app")
j_app.configureProject("%{wks.location}", "JApp", "Sandbox")

workspace "JApp"
	architecture "x64"
	characterset ("MBCS")
	startproject "Sandbox"

project "JApp"
	location "JApp"
	language "C++"
	cppdialect "C++17"
	systemversion "latest"
	uuid(j_app.getUuid())
	kind "StaticLib"

	targetdir(bin_dir)
	objdir(bin_int_dir)

	postbuildcommands {
		"py %{prj.location}../util/make_include_directory.py"
	}

	files 
	{
		"%{prj.name}/src/**",
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/src/vendor",
		"dependencies/GLEW/include",
		"dependencies/GLFW/include",
	}

	libdirs {
		"dependencies/GLFW/lib",
		"dependencies/GLEW/lib",
	}

	links {
		"glfw3.lib",
		"opengl32",
		"glew32s.lib",
	}

	filter "configurations:Debug"
		symbols "Full"

	filter "configurations:Release"
		optimize "On"

	filter "configurations:Dist"
		optimize "On"
	filter {}

project "Sandbox"
	location "Sandbox"
	language "C++"
	cppdialect "C++17"
	systemversion "latest"

	filter "configurations:Debug"
		kind "ConsoleApp"

	filter "configurations:Release"
		kind "ConsoleApp"

	filter "configurations:Dist"
		kind "WindowedApp"
		entrypoint "mainCRTStartup"
	
	filter {}

	targetdir(bin_dir)
	objdir(bin_int_dir)

	includedirs {
		"src",
	}

	files 
	{
		"%{prj.name}/resources/**",
		"%{prj.name}/src/**",
	}

	filter "configurations:Debug"
		targetsuffix ("-dbg")

	filter "configurations:Release"
		targetsuffix ("-rls")

	filter "configurations:Dist"

	filter {}
