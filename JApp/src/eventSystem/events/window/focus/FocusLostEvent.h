#pragma once

#include "FocusEvent.h"

struct FocusGainedEvent : FocusEvent<FocusGainedEvent> {
	FocusGainedEvent() : FocusEvent("gained", true) {}
};