#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "eventSystem/EventListener.h"
#include "eventSystem/events/window/ResizeEvent.h"
#include "eventSystem/events/input/keyboard/KeyPressEvent.h"

namespace JApp {

	class Application : public EventListener<ResizeEvent>, EventListener<KeyPressEvent> {
	protected:
		float m_windowWidth, m_windowHeight;
		float m_targetFrameRate, m_timeStep;
		GLFWwindow* m_window;
	public:
		Application();
		virtual ~Application();

		/* main loop */
		void run();

		/* Listener overwrites */
		bool process(ResizeEvent* e) override;
		bool process(KeyPressEvent* e) override;

		/* client functions */
		virtual void render() = 0;
		virtual void update(float dt) = 0;
	};

	Application* createApplication();
}
