#include "ShaderTest.h"
#include <glm/gtc/matrix_transform.hpp>


ShaderTestApplication::ShaderTestApplication() {
	va = new VertexArray();

	// Create something to render
	auto* vertices = new float[5]
	{
		//  radius	glow	col
			.5f,	3.f,	0.647f, 1.f, 0.f,
	};

	vb = new VertexBuffer(vertices, 5 * sizeof(float));
	vbl = new VertexBufferLayout();
	vbl->push<float>(1);
	vbl->push<float>(1);
	vbl->push<float>(3);

	va->addBuffer(vb, vbl);

	delete[] vertices;

	shader = Shader::fromFiles(
		"resources/shaders/shaderTest/testVertexShader.shader",
		"resources/shaders/shaderTest/testGeometryShader.shader",
		"resources/shaders/shaderTest/testFragmentShader.shader"
	);

	shader->bind();
	shader->setUniformMat4("u_model", glm::mat4(1.f));
	shader->setUniform2f("u_position", 0, 0);
}

ShaderTestApplication::~ShaderTestApplication() {
	delete va;
	delete vb;
	delete vbl;
	delete shader;
}

void ShaderTestApplication::render() {
	const float ratio = static_cast<float>(m_windowWidth) / static_cast<float>(m_windowHeight);
	const glm::mat4 view = glm::mat4(1.f);
	const glm::mat4 projection = glm::ortho(-ratio, ratio, -1.f, 1.f, -1.f, 1.f);

	va->bind();
	shader->bind();

	shader->setUniformMat4("u_view", view);
	shader->setUniformMat4("u_proj", projection);

	GL_CALL(glDrawArrays(GL_POINTS, 0, 1));
}
void ShaderTestApplication::update(const float dt) {
	// nothing to update
}
