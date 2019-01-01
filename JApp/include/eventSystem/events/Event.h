#pragma once
#include <vector>
#include <ostream>

#include "eventSystem/events/EventFormat.h"
#include "eventSystem/EventListener.h"

namespace JApp {

	template<class T>
	struct Event {
		// listener interface
		inline static std::vector<EventListener<T>*> listeners;
		static void addListener(EventListener<T>* listener) {
			listeners.push_back(listener);
		}

		std::string type;
		explicit Event(const std::string& type) : type("event." + type) {}
		virtual ~Event() = default;

		std::string format() {
			EventFormat out = EventFormat(type);
			formatData(out);
			return out.str();
		};

		virtual void formatData(EventFormat& format) = 0;
	};

}

template<class T>
std::ostream& operator<<(std::ostream& os, JApp::Event<T>* event) {
	return os << event->format();
}