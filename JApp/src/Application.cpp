#include "Application.h"

#include <iostream>
#include <chrono>

#include "macros.h"

#define NOW std::chrono::steady_clock::now()

namespace JApp {
	
	Application::Application() {
		/* Initialize the GLFW */
		if (!glfwInit()) {
			std::cout << "Can not initialize GLFW!" << std::endl;
			exit(-1);
		}

		/* open gl hints */
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		/* anti aliasing */
		#if !APP_DEBUG
		RELEASE(std::cout << "Using 8 aa-samples" << std::endl);
		glfwWindowHint(GLFW_SAMPLES, 8);
		#endif

		/* window size and hints */
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);

		glfwWindowHint(GLFW_VISIBLE, 0);

		#if APP_DEBUG
		const float scale = .5;
		m_windowWidth = scale * videoMode->width;
		m_windowHeight = scale * videoMode->height;
		printf("Creating debug window w=%.0f, h=%.0f\n", m_windowWidth, m_windowHeight);
		m_targetFrameRate = float(videoMode->refreshRate);
		#else
		m_windowWidth = float(videoMode->width);
		m_windowHeight = float(videoMode->height);
		glfwWindowHint(GLFW_MAXIMIZED, 1);
		glfwWindowHint(GLFW_DECORATED, 0);
		m_targetFrameRate = float(videoMode->refreshRate) * 2;
		#if APP_RELEASE
		printf("Creating release window w=%.0f, h=%.0f (windowed fullscreen, maximized, not decorated)\n", m_windowWidth, m_windowHeight);
		#elif APP_DIST
		// Create dist window (windowed fullscreen, maximized, not decorated, not resizable)
		glfwWindowHint(GLFW_RESIZABLE, 0);
		#endif
		#endif

		m_timeStep = 2.f / m_targetFrameRate;

		/* initialize window */
		m_window = glfwCreateWindow(int(m_windowWidth), int(m_windowHeight), "Ultimate Wallpaper", nullptr, nullptr);
		if (!m_window) {
			RELEASE(std::cout << "Can not create window!" << std::endl);
			glfwTerminate();
			exit(-1);
		}

		/* window position */
		# if APP_DEBUG
		// p = (screen_size - window_size) / 2, (screen_size - screen_size * scale) / 2 = screen_size * (1 - scale) / 2
		const float f = (1.f - scale) / 2;
		const auto px = int(m_windowWidth * f);
		const auto py = int(m_windowHeight * f);

		printf("Centering window, pos x=%d, y=%d\n", px, py);
		glfwSetWindowPos(m_window, px, py);
		#endif

		/* Make the window's context current */
		glfwMakeContextCurrent(m_window);

		/* set vsync */
		#if APP_DIST || APP_RELEASE
		RELEASE(std::cout << "Vsync on" << std::endl);
		glfwSwapInterval(1);
		#else
		std::cout << "Vsync off" << std::endl;
		glfwSwapInterval(0);
		#endif

		/* Initialize GLEW */
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK) {
			RELEASE(std::cout << "Can not initialize GLEW!" << std::endl);
			glfwTerminate();
			exit(-1);
		}

		/* enable anti aliasing in open gl */
		#if (!APP_DEBUG)
		GL_CALL(glEnable(GL_MULTISAMPLE));
		#endif

		/* set up event system */
		// EventSystem::setWindow(m_window);
		// EventSystem::addListener(static_cast<Listener<WindowResizeEvent>*>(this));
		// EventSystem::addListener(static_cast<Listener<KeyEvent>*>(this));
	}

	Application::~Application() {
		glfwTerminate();
	}

	void Application::run()
	{
		/* show window */
		glfwShowWindow(m_window);
		
		/* Fps counter */
		RELEASE(
			float frameTimes = 0;
			float frames = 0;
			float updates = 0;
		)

		auto lastNow = NOW;
		RELEASE(auto last = NOW);

		float excess = 0;
		while (!glfwWindowShouldClose(m_window)) {
			auto now = NOW;
			const float dt = (now - lastNow).count() / 1e9f;
			lastNow = now;
			excess += dt;

			/* Update game logic*/
			while (m_timeStep <= excess) {
				excess -= m_timeStep;
				RELEASE(updates++);

				/* update here */
				update(m_timeStep);
			}

			RELEASE(auto renderStart = NOW);

			/* render */
			glClear(GL_COLOR_BUFFER_BIT);
			render();
			glfwSwapBuffers(m_window);

			/* Update fps stats */
			RELEASE(
				frames++;
				now = NOW;
				frameTimes += (now - renderStart).count() / 1e9f;
			)

			/* Poll for and process events */
			glfwPollEvents();

			/* Log fps */
			RELEASE(
				float sinceLast = 1.f * (now - last).count();
				if (1e9 < sinceLast) {
					// update global stats
					sinceLast /= 1e9f;
					const float fps = frames / sinceLast;
					const float ups = updates / sinceLast;
					const float frameTimeMs = frameTimes / frames * 1000;
					printf("fps=%.6f, ups=%.2f, frame time=%.6fms\n", fps, ups, frameTimeMs);

					frames = 0;
					updates = 0;
					frameTimes = 0;
					last = NOW;
				}
			)
		}

		/* Hide window */
		glfwHideWindow(m_window);
	}

}
