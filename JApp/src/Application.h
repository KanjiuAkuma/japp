#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace JApp {

	class Application {
	protected:
		float m_windowWidth, m_windowHeight;
		float m_targetFrameRate, m_timeStep;
		GLFWwindow* m_window;
	public:
		Application();
		virtual ~Application();

		void run();

		virtual void render() = 0;
		virtual void update(float dt) = 0;
	};

	Application* createApplication();
}
