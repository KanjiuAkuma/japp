#pragma once
#include "KeyEvent.h"

struct KeyReleaseEvent : KeyEvent<KeyReleaseEvent> {
	KeyReleaseEvent(const int key, const int scanCode, const int mods) : KeyEvent("release", key, scanCode, KEY_RELEASE, mods) {}
};