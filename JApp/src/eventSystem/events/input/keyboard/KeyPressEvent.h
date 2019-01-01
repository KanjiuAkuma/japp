#pragma once
#include "KeyEvent.h"

namespace JApp {

	struct KeyPressEvent : KeyEvent<KeyPressEvent> {
		KeyPressEvent(const int key, const int scanCode, const int mods) : KeyEvent("press", key, scanCode, PRESS, mods) {}
	};

}
