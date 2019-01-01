#pragma once

#include "MouseButtonEvent.h"

namespace JApp {

	struct MouseButtonReleaseEvent : MouseButtonEvent<MouseButtonReleaseEvent> {
		MouseButtonReleaseEvent(const float x, const float y, const int button, const int mods)
			: MouseButtonEvent("press", x, y, button, RELEASE, mods) {}
	};

}