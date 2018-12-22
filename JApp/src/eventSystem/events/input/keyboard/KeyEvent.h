#pragma once

#include "eventSystem/events/input/InputEvent.h"
#include "eventSystem/events/EventFormat.h"

#define KEY_PRESS 0
#define KEY_RELEASE 1
#define KEY_REPEAT 2

template<class T>
struct KeyEvent : InputEvent<T> {
	const int key, scanCode, action, mods;
	explicit KeyEvent(const std::string& type, const int key, const int scanCode, const int action, const int mods) 
		: InputEvent("key." + type), key(key), scanCode(scanCode), action(action), mods(mods) {}
	virtual ~KeyEvent() = default;

	void formatData(EventFormat& format) override {
		format.append("key", key);
		format.append("action", action);
		format.append("scanCode", scanCode);
		format.append("mods", mods);
	}
};