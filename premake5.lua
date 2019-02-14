out_dir = "%{wks.location}/build/"
bin_dir = out_dir .. "bin/%{prj.name}/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
bin_int_dir = out_dir .. "bin-int/%{prj.name}/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

j_app = require("util/j_app")

workspace "JApp"
	architecture "x64"
	characterset ("MBCS")

    configurations {
        "Debug",
        "Release",
        "Dist"
    }

project "JApp"
	location "JApp"
	language "C++"
	cppdialect "C++17"
	systemversion "latest"
	uuid(j_app.getUuid())
	kind "StaticLib"

	targetdir(bin_dir)
	objdir(bin_int_dir)

	files
	{
		"%{prj.name}/src/**",
		"%{prj.name}/include/**",
	}

	includedirs {
		"%{prj.name}/include",
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
