#include "Application.h"
#include <iostream>

namespace JApp {
	
	Application::Application() = default;

	Application::~Application() = default;

	void Application::run()
	{
		std::cout << "Running!" << std::endl;
	}

}
