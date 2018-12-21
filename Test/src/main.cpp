#include "entryPoint.h"

class TestApplication : public JApp::Application {

public:
	void render() override {
		
	}
	void update(const float dt) override {
		
	}
};

JApp::Application* JApp::createApplication() {
	return new TestApplication();
}