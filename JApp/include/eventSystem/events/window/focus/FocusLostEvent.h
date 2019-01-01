#pragma once

#include "FocusEvent.h"

namespace JApp {

	struct FocusGainedEvent : FocusEvent<FocusGainedEvent> {
		FocusGainedEvent() : FocusEvent("gained", true) {}
	};

}