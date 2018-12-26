#pragma once

#include <iostream>
#include <ctime>

#include "logger/Log.h"
#include "macros.h"
#include "application/Application.h"

#if APP_PLATFORM_WINDOWS
// ReSharper disable once CppNonInlineFunctionDefinitionInHeaderFile
int main() {
	Log::init();
	/* seed random */
	std::srand(std::time(nullptr));

	// init log system
	APP_CORE_INFO("Configuration {}", APP_CONFIGURATION);
	// create app
	JApp::Application* app = JApp::createApplication();

	// run
	app->run();

	// delete
	delete app;
	RELEASE(
	std::cout << "Press any key to exit... ";
	std::cin.get();
	)
	return 0;
}
#else
// ReSharper disable once CppNonInlineFunctionDefinitionInHeaderFile
int main() {
	APP_CORE_FATAL("Error windows support only");
	return 0;
}
#endif

