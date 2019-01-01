#pragma once

#include "MouseEvent.h"

namespace JApp {

	struct MouseEnterEvent : MouseEvent<MouseEnterEvent> {

		explicit MouseEnterEvent(const float x, const float y) : MouseEvent("enter", x, y) {}
	};

}