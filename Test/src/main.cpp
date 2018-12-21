#include "entryPoint.h"

JApp::Application* JApp::createApplication() {
	return new Application();
}