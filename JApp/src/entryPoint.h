#pragma once

#include <iostream>
#include "macros.h"
#include "application/Application.h"

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

