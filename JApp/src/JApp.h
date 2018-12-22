#pragma once
/* --------- Header to be included by client --------- */
/// macros
#include "macros.h"

/// application (should be about the first include as it includes glew.h before glfw3.h)
#include "application/Application.h"

/// events
#include "eventSystem/EventSystem.h"
#include "eventSystem/EventListener.h"
#include "eventSystem/events/Events.h"


/* ------------------- Entry point --------------------*/
#include "entryPoint.h"