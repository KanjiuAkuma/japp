#pragma once

#include "application/Application.h"
#include "renderer/vertexArray/VertexArray.h"
#include "renderer/vertexBuffer/VertexBuffer.h"
#include "renderer/vertexBufferLayout/VertexBufferLayout.h"
#include "renderer/shader/Shader.h"

class ShaderTestApplication : public JApp::Application {
	VertexArray* va;
	VertexBuffer* vb;
	VertexBufferLayout* vbl;
	Shader* shader;

public:
	explicit ShaderTestApplication();
	~ShaderTestApplication();
	void render() override;
	void update(float dt) override;
};
