out_dir = "%{wks.location}/build/"
bin_dir = out_dir .. "bin/%{prj.name}/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
bin_int_dir = out_dir .. "bin-int/%{prj.name}/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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

include("JApp/premake5.lua")
include("Test/premake5.lua")