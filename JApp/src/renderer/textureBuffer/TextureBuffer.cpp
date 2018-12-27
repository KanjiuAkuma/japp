#include "TextureBuffer.h"

#include "macros.h"
#include <GL/glew.h>

TextureBuffer::TextureBuffer(float* data, const unsigned int elements) {
	GL_CALL(glGenBuffers(1, &m_buffId));
	GL_CALL(glBindBuffer(GL_TEXTURE_BUFFER, m_buffId));
	GL_CALL(glBufferData(GL_TEXTURE_BUFFER, elements * sizeof(float), data, GL_STATIC_DRAW));

	GL_CALL(glGenTextures(1, &m_rendererId));

	GL_CALL(glActiveTexture(GL_TEXTURE0 + 2));
	GL_CALL(glBindTexture(GL_TEXTURE_BUFFER, m_rendererId));
	GL_CALL(glTexBuffer(GL_TEXTURE_BUFFER, GL_R32F, m_buffId));
}

TextureBuffer::~TextureBuffer() {
	GL_CALL(glDeleteTextures(1, &m_rendererId));
	GL_CALL(glDeleteBuffers(1, &m_buffId));
}

void TextureBuffer::bind(const unsigned int slot) const {
	GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, m_rendererId));
}

void TextureBuffer::unbind() const {
	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}
