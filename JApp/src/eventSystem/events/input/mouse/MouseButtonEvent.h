#pragma once

#include "MouseEvent.h"

#define MOUSE_BUTTON_PRESS 0
#define MOUSE_BUTTON_RELEASE 1
#define MOUSE_BUTTON_REPEAT 2

template<class T>
struct MouseButtonEvent : MouseEvent<T> {
	const int button, action, mods;
	MouseButtonEvent(const std::string& type, const float x, const float y, const int button, const int action, const int mods)
		: MouseEvent("button." + type, x, y), button(button), action(action), mods(mods) {}
	virtual ~MouseButtonEvent() = default;

	void formatData(EventFormat& format) override {
		MouseEvent<T>::formatData(format);
		format.append("button", button);
		format.append("action=", action);
		format.append("mods", mods);
	}
};