project "Test"
	location "%{wks.location}/Test"
	language "C++"
	cppdialect "C++17"
	systemversion "latest"
	kind "ConsoleApp"

	targetdir(bin_dir)
	objdir(bin_int_dir)

	links {
		"JApp",
	}

	includedirs {
		"src",
		"JApp/src",
	}

	files 
	{
		"src/**.h",
		"src/**.cpp",
	}

	filter "system:windows"
		defines {
			"APP_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines {
			"APP_DEBUG"
		}

	filter "configurations:Release"
		defines {
			"APP_RELEASE"
		}

	filter "configurations:Dist"
		defines {
			"APP_DIST"
		}