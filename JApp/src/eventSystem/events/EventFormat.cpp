#include "eventSystem/events/EventFormat.h"

namespace JApp {

	EventFormat::EventFormat(const std::string& type) {
		stream << type;
	}

	std::string EventFormat::str() const {
		return stream.str();
	}

}