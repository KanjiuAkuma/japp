#pragma once

#include "MouseEvent.h"

namespace JApp {

	template<class T>
	struct MouseButtonEvent : MouseEvent<T> {

		enum Action {
			PRESS,
			RELEASE,
			REPEAT,
		};

		const int button, mods;
		const Action action;

		MouseButtonEvent(const std::string& type, const float x, const float y, const int button, const Action action, const int mods)
			: MouseEvent("button." + type, x, y), button(button), mods(mods), action(action) {}
		virtual ~MouseButtonEvent() = default;

		void formatData(EventFormat& format) override {
			MouseEvent<T>::formatData(format);
			format.append("button", button);
			format.append("action=", action);
			format.append("mods", mods);
		}
	};

}