#pragma once

#include "application/Application.h"
#include "renderer/Renderer.h"

class TextureTestApplication : public JApp::Application {
	VertexArray* va;
	VertexBuffer* vb;
	VertexBufferLayout* vbl;
	IndexBuffer* ib;
	Shader* shader;
	Texture* texture;

public:
	explicit TextureTestApplication();
	~TextureTestApplication();
	void render() override;
	void update(float dt) override;
};
