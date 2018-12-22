m = {}

local m_uuid = "df766ed3-e589-48a1-a889-5dd16787f0bb"

function m.createHere()
	project "JApp"
		location "JApp"
		language "C++"
		cppdialect "C++17"
		systemversion "latest"
		uuid(m_uuid)
		kind "StaticLib"

		targetdir(bin_dir)
		objdir(bin_int_dir)

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

		filter "system:windows"
			defines {
				"APP_PLATFORM_WINDOWS"
			}

		filter "configurations:Debug"
			symbols "Full"
			defines {
				"APP_DEBUG"
			}

		filter "configurations:Release"
			optimize "On"
			defines {
				"APP_RELEASE"
			}

		filter "configurations:Dist"
			optimize "On"
			defines {
				"APP_DIST"
			}
		filter {}
end

function m.includeHere(j_app_path)
externalproject "JApp"
	location(j_app_path .. "/JApp")
	uuid(m_uuid)
	language "C++"
	cppdialect "C++17"
	systemversion "latest"
	kind "StaticLib"
end

function m.configureThis(j_app_path)
	filter "configurations:Debug"
		kind "ConsoleApp"

	filter "configurations:Release"
		kind "ConsoleApp"

	filter "configurations:Dist"
		kind "WindowedApp"
		entrypoint "mainCRTStartup"
	
	filter {}

	includedirs {
		j_app_path .. "/JApp/src",
		j_app_path .. "/JApp/src/vendor",
		j_app_path .. "/dependencies/GLEW/include",
		j_app_path .. "/dependencies/GLFW/include",
	}

	libdirs {
		j_app_path .. "/dependencies/GLFW/lib",
		j_app_path .. "/dependencies/GLEW/lib",
	}

	links {
		"glfw3.lib",
		"opengl32",
		"glew32s.lib",
		"JApp",
	}

	filter "system:windows"
		defines {
			"APP_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		targetsuffix ("-dbg")
		symbols "Full"
		defines {
			"APP_DEBUG"
		}

	filter "configurations:Release"
		targetsuffix ("-rls")
		optimize "On"
		defines {
			"APP_RELEASE"
		}

	filter "configurations:Dist"
		optimize "On"
		defines {
			"APP_DIST"
		}
	filter {}
end

return m;