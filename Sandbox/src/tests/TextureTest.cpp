#include "TextureTest.h"

#include <glm/gtc/matrix_transform.hpp>

#include "util/image/ImageLoader.h"

TextureTestApplication::TextureTestApplication() {
	const auto* vertices = new float[4 * 4]
	{
		//  Position    Texture Coordinates
			-1.f, -1.f, -0.2f, -0.2f,	// ll
			 1.f, -1.f,  1.2f, -0.2f,	// rl
			 1.f,  1.f,  1.2f,  1.2f,	// ru
			-1.f,  1.f, -0.2f,  1.2f	// lu
	};

	va = new VertexArray();

	vb = new VertexBuffer(vertices, 4 * 4 * sizeof(float));
	vbl = new VertexBufferLayout();
	vbl->push<float>(2);
	vbl->push<float>(2);

	va->addBuffer(vb, vbl);

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,
	};

	/* create index buffer */
	ib = new IndexBuffer(indices, 6);

	delete[] vertices;

	shader = Shader::fromFiles(
		"resources/shaders/textureTest/testVertexShader.shader",
		"resources/shaders/textureTest/testFragmentShader.shader"
	);

	/* load texture */
	// ImageLoader ldr = ImageLoader("resources/textures/testTexture.png");
	// ldr.start();
	// ldr.join();
	// texture = Texture::fromValues(ldr.getImage(), ldr.getImageWidth(), ldr.getImageHeight());
	float values[]
	{
		0.00f, 0.25f, 0.5, 0.75f, 1.f,
		0.00f, 0.25f, 0.5, 0.75f, 1.f,
		0.00f, 0.25f, 0.5, 0.75f, 1.f,
		0.00f, 0.25f, 0.5, 0.75f, 1.f,
		0.00f, 0.25f, 0.5, 0.75f, 1.f,
	};

	texture = Texture::fromValues(values, 2, 2);

	/* bind texture */
	shader->bind();
	const int textureSlot = 0;
	texture->bind(textureSlot);
	shader->setUniform1i("u_Texture", textureSlot);
}
TextureTestApplication::~TextureTestApplication() {
	delete va;
	delete vb;
	delete vbl;
	delete ib;
	delete shader;
	delete texture;
}
void TextureTestApplication::render() {
	const float ratio = static_cast<float>(m_windowWidth) / static_cast<float>(m_windowHeight);
	const glm::mat model = glm::scale(glm::mat4(1.f), glm::vec3(ratio, 1, 1));
	const glm::mat4 view = glm::mat4(1.f);
	const glm::mat4 projection = glm::ortho(-ratio, ratio, -1.f, 1.f, -1.f, 1.f);

	va->bind();
	ib->bind();
	shader->bind();

	shader->setUniformMat4("u_model", model);
	shader->setUniformMat4("u_view", view);
	shader->setUniformMat4("u_proj", projection);

	GL_CALL(glDrawElements(GL_TRIANGLES, ib->getCount(), GL_UNSIGNED_INT, nullptr));
}
void TextureTestApplication::update(const float dt) {
	// nothing to update
}
