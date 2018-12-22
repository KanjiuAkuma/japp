#pragma once

#include "MouseEvent.h"

struct MouseExitEvent : MouseEvent<MouseExitEvent> {
	explicit MouseExitEvent(const float x, const float y) : MouseEvent("exit", x, y) {}
};