#pragma once

#include "MouseEvent.h"

struct MouseEnterEvent : MouseEvent<MouseEnterEvent> {

	explicit MouseEnterEvent(const float x, const float y) : MouseEvent("enter", x, y) {}
};
