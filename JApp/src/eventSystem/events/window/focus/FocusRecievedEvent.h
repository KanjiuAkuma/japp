#pragma once

#include "FocusEvent.h"

struct FocusLostEvent : FocusEvent<FocusLostEvent> {
	FocusLostEvent() : FocusEvent("lost", false) {}
};