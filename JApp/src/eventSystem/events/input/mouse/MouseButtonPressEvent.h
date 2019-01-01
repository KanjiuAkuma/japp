#pragma once

#include "MouseButtonEvent.h"

namespace JApp {

	struct MouseButtonPressEvent : MouseButtonEvent<MouseButtonPressEvent> {
		MouseButtonPressEvent(const float x, const float y, const int button, const int mods)
			: MouseButtonEvent("press", x, y, button, PRESS, mods) {}
	};

}