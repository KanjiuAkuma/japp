#include "TextureTest.h"

#include <glm/gtc/matrix_transform.hpp>

#include "util/image/ImageLoader.h"

TextureTestApplication::TextureTestApplication() {

	float cube[] {
	   -1.0f,-1.0f,-1.0f, // triangle 1 : begin
	   -1.0f,-1.0f, 1.0f,
	   -1.0f, 1.0f, 1.0f, // triangle 1 : end

		1.0f, 1.0f,-1.0f, // triangle 2 : begin
	   -1.0f,-1.0f,-1.0f,
	   -1.0f, 1.0f,-1.0f, // triangle 2 : end

		1.0f,-1.0f, 1.0f,
	   -1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,

		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
	   -1.0f,-1.0f,-1.0f,

	   -1.0f,-1.0f,-1.0f,
	   -1.0f, 1.0f, 1.0f,
	   -1.0f, 1.0f,-1.0f,

		1.0f,-1.0f, 1.0f,
	   -1.0f,-1.0f, 1.0f,
	   -1.0f,-1.0f,-1.0f,

	  -1.0f, 1.0f, 1.0f,
	  -1.0f,-1.0f, 1.0f,
	   1.0f,-1.0f, 1.0f,

	   1.0f, 1.0f, 1.0f,
	   1.0f,-1.0f,-1.0f,
	   1.0f, 1.0f,-1.0f,

	   1.0f,-1.0f,-1.0f,
	   1.0f, 1.0f, 1.0f,
	   1.0f,-1.0f, 1.0f,

		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
	   -1.0f, 1.0f,-1.0f,

		1.0f, 1.0f, 1.0f,
	   -1.0f, 1.0f,-1.0f,
	   -1.0f, 1.0f, 1.0f,

	   1.0f, 1.0f, 1.0f,
	  -1.0f, 1.0f, 1.0f,
	   1.0f,-1.0f, 1.0f
	};

	float uvKoord[] {
			0.0f, 0.0f,  // lower-left corner  
			1.0f, 0.0f,  // lower-right corner
			0.5f, 1.0f
	};

	unsigned int vbold1;
	GL_CALL(glGenBuffers(1, &vbold1));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbold1));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(float), cube, GL_STATIC_DRAW));
	GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0));
	GL_CALL(glEnableVertexAttribArray(0));

	unsigned int vbold2;
	GL_CALL(glGenBuffers(1, &vbold2));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbold2));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), uvKoord, GL_STATIC_DRAW));
	GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0));
	GL_CALL(glEnableVertexAttribArray(0));


	shader = Shader::fromFiles(
		"resources/shaders/textureTest/testVertexShader.shader",
		"resources/shaders/textureTest/testFragmentShader.shader"
	);

	texture = Texture::fromFile("resources/textures/pikatchuTex.jpg");

	/* bind texture */
	shader->bind();
	const int textureSlot = 1;
	texture->bind(textureSlot);
	shader->setUniform1i("u_texture", textureSlot);
}
TextureTestApplication::~TextureTestApplication() {
	// delete va1;
	// delete vb1;
	// delete vbl1;
	// delete va2;
	// delete vb2;
	// delete vbl2;
	delete shader;
	delete texture;
}
void TextureTestApplication::render() {
	const float ratio = static_cast<float>(m_windowWidth) / static_cast<float>(m_windowHeight);
	glm::mat model = glm::rotate(glm::mat4(1.f), glm::radians(rotation), glm::vec3(1.f, 1.f, 0.f));
	model = glm::scale(model, glm::vec3(.5f, .5f, .5f));
	const glm::mat4 view = glm::mat4(1.f);
	const glm::mat4 projection = glm::ortho(-ratio, ratio, -1.f, 1.f, -1.f, 1.f);
	
	shader->bind();

	shader->setUniformMat4("u_model", model);
	shader->setUniformMat4("u_view", view);
	shader->setUniformMat4("u_proj", projection);

	GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 36));
}
void TextureTestApplication::update(const float dt) {
	rotation = glm::mod(rotation + 45.f * dt, 360.f);
}
