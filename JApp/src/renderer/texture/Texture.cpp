#include "Texture.h"

#include "macros.h"
#include <GL/glew.h>

#include <stb/stb_image.h>

Texture::Texture(unsigned char* image, const int width, const int height) {
	// create texture
	GL_CALL(glGenTextures(1, &m_RendererID));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
		
	/* setup texture scaling and wrapping */
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	// load image into gpu
	GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image));
	
	// clean up
	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture::Texture(float* data, const int width, const int height) {
	// create texture
	GL_CALL(glGenTextures(1, &m_RendererID));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	/* setup texture scaling and wrapping */
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	// load image into gpu
	GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, width, height, 0, GL_RED, GL_FLOAT, data));

	// clean up
	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture::~Texture()
{
	GL_CALL(glDeleteTextures(1, &m_RendererID));
}

void Texture::bind(const unsigned int slot) const
{
	GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::unbind() const
{
	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture* Texture::fromFile(const std::string& path) {
	// load image
	stbi_set_flip_vertically_on_load(1);
	int width, height, bitsPerPixel;
	unsigned char* image = stbi_load(path.c_str(), &width, &height, &bitsPerPixel, 4);

	// create texture
	auto* out = new Texture(image, width, height);
	
	// free image
	if (image) stbi_image_free(image);
	return out;
}
Texture* Texture::fromValues(unsigned char* image, const int width, const int height) {
	return new Texture(image, width, height);
}

Texture* Texture::fromValues(float* data, const int width, const int height) {
	return new Texture(data, width, height);
}