#pragma once

#include "eventSystem/events/window/WindowEvent.h"
#include "eventSystem/events/EventFormat.h"

struct ResizeEvent : WindowEvent<ResizeEvent> {
	const int width, height;
	explicit ResizeEvent(const int width, const int height) : WindowEvent("resize"), width(width), height(height) {}

	void formatData(EventFormat& format) override {
		format.append("width", width);
		format.append("height", height);
	}
};