project "JApp"
	location "%{wks.location}/%{prj.name}"
	language "C++"
	cppdialect "C++17"
	systemversion "latest"
	uuid "df766ed3-e589-48a1-a889-5dd16787f0bb"

	kind "StaticLib"

	targetdir(bin_dir)
	objdir(bin_int_dir)

	defines {
		"GLEW_STATIC",
	}

	files 
	{
		"src/**.h",
		"src/**.cpp",
	}

	includedirs {
		"/src",
		"/src/vendor",
		"%{wks.location}/dependencies/GLEW/include",
		"%{wks.location}/dependencies/GLFW/include",
	}

	libdirs {
		"%{wks.location}/dependencies/GLFW/lib",
		"%{wks.location}/dependencies/GLEW/lib",
	}

	links {
		"glfw3.lib",
		"opengl32",
		"glew32s.lib",
	}