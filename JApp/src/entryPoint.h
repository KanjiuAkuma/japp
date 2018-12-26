#pragma once

#include <iostream>
#include "macros.h"
#include "application/Application.h"
#include <ctime>

#if APP_PLATFORM_WINDOWS
// ReSharper disable once CppNonInlineFunctionDefinitionInHeaderFile
int main() {
	/* seed random */
	std::srand(std::time(nullptr));

	// init log system
	std::cout << "Configuration " << APP_CONFIGURATION << std::endl;

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
	std::cout << "Error windows support only" << std::endl;
	return 0;
}
#endif

