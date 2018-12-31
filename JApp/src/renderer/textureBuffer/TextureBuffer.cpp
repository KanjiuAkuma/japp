#include "TextureBuffer.h"

#include "macros.h"
#include <GL/glew.h>

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
	GL_CALL(glBindBuffer(GL_TEXTURE_BUFFER, m_bufferId));
	GL_CALL(glBufferData(GL_TEXTURE_BUFFER, width * height * sizeof(float), data, GL_STATIC_DRAW));
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
