#pragma once
#include "KeyEvent.h"

namespace JApp {

	struct KeyReleaseEvent : KeyEvent<KeyReleaseEvent> {
		KeyReleaseEvent(const int key, const int scanCode, const int mods) : KeyEvent("release", key, scanCode, RELEASE, mods) {}
	};

}