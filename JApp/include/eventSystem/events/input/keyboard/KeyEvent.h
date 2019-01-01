#pragma once

#include "eventSystem/events/input/InputEvent.h"
#include "eventSystem/events/EventFormat.h"

namespace JApp {

	template<class T>
	struct KeyEvent : InputEvent<T> {
		enum Action {
			PRESS,
			RELEASE,
			REPEAT,
		};

		const int key, scanCode, mods;
		const Action action;
		explicit KeyEvent(const std::string& type, const int key, const int scanCode, const Action action, const int mods)
			: InputEvent("key." + type), key(key), scanCode(scanCode), mods(mods), action(action) {}
		virtual ~KeyEvent() = default;

		void formatData(EventFormat& format) override {
			format.append("key", key);
			format.append("action", action);
			format.append("scanCode", scanCode);
			format.append("mods", mods);
		}
	};

}