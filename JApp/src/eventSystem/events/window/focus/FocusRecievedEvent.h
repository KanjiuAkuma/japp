#pragma once

#include "FocusEvent.h"

namespace JApp {

	struct FocusLostEvent : FocusEvent<FocusLostEvent> {
		FocusLostEvent() : FocusEvent("lost", false) {}
	};

}