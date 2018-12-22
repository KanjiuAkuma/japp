#pragma once

#include "MouseButtonEvent.h"

struct MouseButtonRepeatEvent : MouseButtonEvent<MouseButtonRepeatEvent> {
	MouseButtonRepeatEvent(const float x, const float y, const int button, const int mods)
		: MouseButtonEvent("press", x, y, button, MOUSE_BUTTON_REPEAT, mods) {}
};