#include "JApp.h"
#include "tests/AppTest.h"
#include "tests/ShaderTest.h"
#include "tests/TextureTest.h"

JApp::Application* JApp::createApplication() {
	/* test application */
	// return new TestApplication();
	/* test shader */
	return new ShaderTestApplication();
	/* test texture */
	// return new TextureTestApplication();
}

