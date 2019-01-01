#pragma once

#include "eventSystem/events/input/InputEvent.h"
#include "eventSystem/events/EventFormat.h"

namespace JApp {

	struct DropEvent : InputEvent<DropEvent> {
		const int fileCount;
		const char** paths;

		DropEvent(const int fileCount, const char** paths) : InputEvent("drop"), fileCount(fileCount), paths(paths) {}

		void formatData(EventFormat& format) override {
			format.append("file count", fileCount);
			for (int i = 0; i < fileCount; i++) {
				format.append(&"file"[i], paths[i]);
			}
		}
	};

}