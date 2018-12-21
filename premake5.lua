out_dir = "%{wks.location}/build/"
bin_dir = out_dir .. "bin/%{prj.name}/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
bin_int_dir = out_dir .. "bin-int/%{prj.name}/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

j_app = require("j_app")

workspace "JApp"
	architecture "x64"
	characterset ("MBCS")
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist",
	}

	defines {
		"GLEW_STATIC"
	}

j_app.createHere()

project "Sandbox"
	location "Sandbox"
	language "C++"
	cppdialect "C++17"
	systemversion "latest"
	
	j_app.configureThis("%{wks.location}")

	targetdir(bin_dir)
	objdir(bin_int_dir)

	includedirs {
		"src",
	}

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}