#pragma once

#include "MouseButtonEvent.h"

struct MouseButtonReleaseEvent : MouseButtonEvent<MouseButtonReleaseEvent> {
	MouseButtonReleaseEvent(const float x, const float y, const int button, const int mods)
		: MouseButtonEvent("press", x, y, button, MOUSE_BUTTON_RELEASE, mods) {}
};