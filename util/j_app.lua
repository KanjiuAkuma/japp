m = {}

local m_uuid = "df766ed3-e589-48a1-a889-5dd16787f0bb"

function m.getUuid()
return m_uuid
end

function m.includeJApp(j_app_path)
externalproject "JApp"
	location(j_app_path .. "/JApp")
	uuid(m_uuid)
	language "C++"
	cppdialect "C++17"
	systemversion "latest"
	kind "StaticLib"
end

function m.configureProject(j_app_path, workspace_name, project_name)
workspace(workspace_name)


	configurations
	{
		"Debug",
		"Release",
		"Dist",
	}

	defines {
		"GLEW_STATIC"
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

	project(project_name)
		includedirs {
			j_app_path .. "/include",
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
end

return m;
