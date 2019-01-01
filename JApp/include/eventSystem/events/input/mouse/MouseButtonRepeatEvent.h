#pragma once

#include "MouseButtonEvent.h"

namespace JApp {

	struct MouseButtonRepeatEvent : MouseButtonEvent<MouseButtonRepeatEvent> {
		MouseButtonRepeatEvent(const float x, const float y, const int button, const int mods)
			: MouseButtonEvent("press", x, y, button, REPEAT, mods) {}
	};

}