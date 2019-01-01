#pragma once

#include "macros.h"
#include <GLFW/glfw3.h>

#include "EventListener.h"

namespace JApp {

	class EventSystem {
		inline static GLFWwindow* WINDOW;

		template <typename T>
		static void processEvent(T* event) {
			for (unsigned int i = 0; i < T::listeners.size(); i++) {
				if (T::listeners[i]->process(event)) break;
			}
		}

	public:
		template <class T>
		static void registerListener(EventListener<T>* l) {
			T::addListener(l);
		}

		static void setWindow(GLFWwindow* window);

		static void sizeCallback(GLFWwindow* window, int width, int height);
		static void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void mouseWheelCallback(GLFWwindow* window, double dx, double dy);
		static void focusCallback(GLFWwindow* window, int focused);
		static void cursorEnterCallback(GLFWwindow* window, int entered);
		static void dropCallback(GLFWwindow* window, int fileCount, const char** paths);
	};

}