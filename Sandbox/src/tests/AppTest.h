#pragma once
#include "application/Application.h"

class TestApplication : public JApp::Application {

public:
	void render() override;
	void update(const float dt) override;
};