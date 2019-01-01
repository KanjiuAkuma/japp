#pragma once
#include "KeyEvent.h"

namespace JApp {

	struct KeyRepeatEvent : KeyEvent<KeyRepeatEvent> {
		KeyRepeatEvent(const int key, const int scanCode, const int mods) : KeyEvent("release", key, scanCode, REPEAT, mods) {}
	};

}