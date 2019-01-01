#pragma once

#include "eventSystem/events/Event.h"

namespace JApp {

	template<class T>
	struct InputEvent : Event<T> {
		explicit InputEvent(const std::string& type) : Event("input." + type) {}
		virtual ~InputEvent() = default;
	};

}