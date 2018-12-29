#include "TextureBuffer.h"

#include "macros.h"
#include <GL/glew.h>

#if 0
TextureBuffer::TextureBuffer(float* data, const unsigned int width, const unsigned int height) {
	// create texture
	GL_CALL(glGenTextures(1, &m_rendererId));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, m_rendererId));

	/* setup texture scaling and wrapping */
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

	// load data into gpu
	// GL_CALL(glTexImage2D(GL_TEXTURE_2D, 1, GL_R32F, width, height, 0, GL_RED, GL_FLOAT, data));
	GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, width, height, 0, GL_RED, GL_FLOAT, data));

	// clean up
	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}
#endif

TextureBuffer::TextureBuffer() {
	GL_CALL(glGenBuffers(1, &m_bufferId));
	GL_CALL(glBindBuffer(GL_TEXTURE_BUFFER, m_bufferId));
	GL_CALL(glGenTextures(1, &m_textureId));
	GL_CALL(glBindBuffer(GL_TEXTURE_BUFFER, 0));
}

TextureBuffer::~TextureBuffer() {
	GL_CALL(glDeleteBuffers(1, &m_bufferId));
	GL_CALL(glDeleteTextures(1, &m_textureId));
}

void TextureBuffer::setData(float* data, const unsigned int width, const unsigned int height) {
	// GL_CALL(glBindTexture(GL_TEXTURE_BUFFER, m_textureId));
	GL_CALL(glBindBuffer(GL_TEXTURE_BUFFER, m_bufferId));
	GL_CALL(glBufferData(GL_TEXTURE_BUFFER, width * height * sizeof(float), data, GL_STATIC_DRAW));
	// GL_CALL(glBindTexture(GL_TEXTURE_BUFFER, 0));
	GL_CALL(glBindBuffer(GL_TEXTURE_BUFFER, 0));
}

void TextureBuffer::bind(const unsigned int slot) const {
	GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
	GL_CALL(glBindTexture(GL_TEXTURE_BUFFER, m_textureId));
	GL_CALL(glTexBuffer(GL_TEXTURE_BUFFER, GL_R32F, m_bufferId));
}

void TextureBuffer::unbind() const {
	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}
