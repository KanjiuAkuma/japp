#pragma once

#include "MouseEvent.h"

struct MouseScrollEvent : MouseEvent<MouseScrollEvent> {
	const float dx, dy;
	MouseScrollEvent(const float x, const float y, const float dx, const float dy) : MouseEvent("scroll", x, y), dx(dx), dy(dy) {}

	void formatData(EventFormat& format) override {
		MouseEvent<MouseScrollEvent>::formatData(format);
		format.append("dx", dx);
		format.append("dy", dy);
	}
};