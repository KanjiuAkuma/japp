#pragma once

#include "eventSystem/events/window/WindowEvent.h"
#include "eventSystem/events/EventFormat.h"

namespace JApp {

	template<class T>
	struct FocusEvent : WindowEvent<T> {
		const bool focused;
		explicit FocusEvent(const std::string& type, const bool focused) : WindowEvent("focus." + type), focused(focused) {}
		virtual ~FocusEvent() = default;

		void formatData(EventFormat& format) override {
			format.append("focused", focused);
		}
	};

}