#pragma once
#include "KeyEvent.h"

struct KeyRepeatEvent : KeyEvent<KeyRepeatEvent> {
	KeyRepeatEvent(const int key, const int scanCode, const int mods) : KeyEvent("release", key, scanCode, KEY_REPEAT, mods) {}
};