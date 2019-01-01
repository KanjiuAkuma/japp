#pragma once

#include "eventSystem/events/input/InputEvent.h"
#include "eventSystem/events/EventFormat.h"

namespace JApp {

	template<class T>
	struct MouseEvent : InputEvent<T> {
		const float x, y;
		explicit MouseEvent(const std::string& type, const float x, const float y) : InputEvent("mouse." + type), x(x), y(y) {}
		virtual ~MouseEvent() = default;

		void formatData(EventFormat& format) override {
			format.append("x", x);
			format.append("y", y);
		}
	};

}