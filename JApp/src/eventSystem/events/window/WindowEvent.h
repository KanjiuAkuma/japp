#pragma once

#include <eventSystem/events/Event.h>

template<class T>
struct WindowEvent : Event<T> {
	explicit WindowEvent(const std::string& type) : Event("window." + type) {}
	virtual ~WindowEvent() = default;
};