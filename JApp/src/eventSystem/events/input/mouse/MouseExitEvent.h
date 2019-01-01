#pragma once

#include "MouseEvent.h"

namespace JApp {

	struct MouseExitEvent : MouseEvent<MouseExitEvent> {
		explicit MouseExitEvent(const float x, const float y) : MouseEvent("exit", x, y) {}
	};

}