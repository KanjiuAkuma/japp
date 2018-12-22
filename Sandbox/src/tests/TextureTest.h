#pragma once

#include "application/Application.h"
#include "renderer/vertexArray/VertexArray.h"
#include "renderer/vertexBuffer/VertexBuffer.h"
#include "renderer/vertexBufferLayout/VertexBufferLayout.h"
#include "renderer/shader/Shader.h"
#include "renderer/texture/Texture.h"
#include "renderer/indexBuffer/IndexBuffer.h"

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
