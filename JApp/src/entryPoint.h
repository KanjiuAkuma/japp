#pragma once
#include "Application.h"
#include <iostream>

#if APP_DEBUG
#define APP_CONFIGURATION "debug"
#elif APP_RELEASE
#define APP_CONFIGURATION "release"
#elif APP_DIST
#define APP_CONFIGURATION "dist"
#else
#define APP_CONFIGURATION "unknown"
#endif

#if APP_PLATFORM_WINDOWS
// ReSharper disable once CppNonInlineFunctionDefinitionInHeaderFile
int main() {
	// init log system
	std::cout << "Configuration " << APP_CONFIGURATION << std::endl;

	// create app
	JApp::Application* app = JApp::createApplication();

	// run
	app->run();

	// delete
	delete app;
	return 0;
}
#else
// ReSharper disable once CppNonInlineFunctionDefinitionInHeaderFile
int main() {
	std::cout << "Error windows support only" << std::endl;
	return 0;
}
#endif

