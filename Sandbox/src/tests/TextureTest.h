#pragma once

#include "application/Application.h"
#include "renderer/Renderer.h"

using namespace JApp;

class TextureTestApplication : public JApp::Application {
	VertexArray *va1, *va2;
	VertexBuffer *vb1, *vb2;
	VertexBufferLayout *vbl1, *vbl2;
	Shader* shader;
	Texture* texture;
	float rotation = 0;
public:
	explicit TextureTestApplication();
	~TextureTestApplication();
	void render() override;
	void update(float dt) override;
};
