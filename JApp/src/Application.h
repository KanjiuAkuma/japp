#pragma once

namespace JApp {

	class Application {
	public:
		Application();
		virtual ~Application();

		void run();
	};

	Application* createApplication();
}
