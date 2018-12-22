#pragma once
#include "KeyEvent.h"

struct KeyPressEvent : KeyEvent<KeyPressEvent> {
	KeyPressEvent(const int key, const int scanCode, const int mods) : KeyEvent("press", key, scanCode, KEY_PRESS, mods) {}
};
