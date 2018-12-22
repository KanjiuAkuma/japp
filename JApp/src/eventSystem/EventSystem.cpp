#include "EventSystem.h"

#include "macros.h"
#include "events/Events.h"

void EventSystem::setWindow(GLFWwindow* window) {
	// clean old points
	if (WINDOW) {
		glfwSetWindowSizeCallback(WINDOW, nullptr);
		glfwSetKeyCallback(WINDOW, nullptr);
		glfwSetMouseButtonCallback(WINDOW, nullptr);
		glfwSetScrollCallback(WINDOW, nullptr);
		glfwSetWindowFocusCallback(WINDOW, nullptr);
		glfwSetCursorEnterCallback(WINDOW, nullptr);
		glfwSetDropCallback(WINDOW, nullptr);
	}
	WINDOW = window;
	glfwSetWindowSizeCallback(window, &EventSystem::sizeCallback);
	glfwSetKeyCallback(window, &EventSystem::keyCallback);
	glfwSetMouseButtonCallback(window, &EventSystem::mouseButtonCallback);
	glfwSetScrollCallback(window, &EventSystem::mouseWheelCallback);
	glfwSetWindowFocusCallback(window, &EventSystem::focusCallback);
	glfwSetCursorEnterCallback(window, &EventSystem::cursorEnterCallback);
	glfwSetDropCallback(window, &EventSystem::dropCallback);
}

void EventSystem::sizeCallback(GLFWwindow* window, const int width, const int height) {
	ASSERT(window == WINDOW);
	ResizeEvent e = ResizeEvent(width, height);
	processEvent(&e);
}
void EventSystem::keyCallback(GLFWwindow* window, const int key, const int scanCode, const int action, const int mods) {
	ASSERT(window == WINDOW);

	if (action == GLFW_PRESS) {
		KeyPressEvent pe = KeyPressEvent(key, scanCode, mods);
		processEvent(&pe);
	}
	else if (action == GLFW_RELEASE) {
		KeyReleaseEvent re = KeyReleaseEvent(key, scanCode, mods);
		processEvent(&re);
	} 
	else {
		KeyRepeatEvent rpe = KeyRepeatEvent(key, scanCode, mods);
		processEvent(&rpe);
	}
}
void EventSystem::mouseButtonCallback(GLFWwindow* window, const int button, const int action, const int mods) {
	ASSERT(window == WINDOW);

	double dMouseX, dMouseY;
	glfwGetCursorPos(WINDOW, &dMouseX, &dMouseY);

	const float mouseX = float(dMouseX);
	const float mouseY = float(dMouseY);

	if (action == GLFW_PRESS) {
		MouseButtonPressEvent pe = MouseButtonPressEvent(mouseX, mouseY, button, mods);
		processEvent(&pe);
	}
	else if (action == GLFW_RELEASE) {
		MouseButtonReleaseEvent re = MouseButtonReleaseEvent(mouseX, mouseY, button, mods);
		processEvent(&re);
	}
	else {
		MouseButtonRepeatEvent rpe = MouseButtonRepeatEvent(mouseX, mouseY, button, mods);
		processEvent(&rpe);
	}
}

void EventSystem::mouseWheelCallback(GLFWwindow* window, const double dx, const double dy) {
	ASSERT(window == WINDOW);

	double mouseX, mouseY;
	glfwGetCursorPos(WINDOW, &mouseX, &mouseY);
	MouseScrollEvent e = MouseScrollEvent(float(mouseX), float(mouseY), float(dx), float(dy));
	processEvent(&e);
}
void EventSystem::focusCallback(GLFWwindow* window, const int focused) {
	ASSERT(window == WINDOW);

	if (focused) {
		FocusGainedEvent e = FocusGainedEvent();
		processEvent(&e);
	} else {
		FocusLostEvent e = FocusLostEvent();
		processEvent(&e);
	}
	
}
void EventSystem::cursorEnterCallback(GLFWwindow* window, const int entered) {
	ASSERT(window == WINDOW);

	double mouseX, mouseY;
	glfwGetCursorPos(WINDOW, &mouseX, &mouseY);
	if (entered) {
		MouseEnterEvent e = MouseEnterEvent(float(mouseX), float(mouseY));
		processEvent(&e);
	} else {
		MouseExitEvent e = MouseExitEvent(float(mouseX), float(mouseY));
		processEvent(&e);
	}
}
void EventSystem::dropCallback(GLFWwindow* window, const int fileCount, const char** paths) {
	ASSERT(window == WINDOW);

	DropEvent e = DropEvent(fileCount, paths);
	processEvent(&e);
}
