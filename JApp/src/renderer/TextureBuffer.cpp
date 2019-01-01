#include "renderer/TextureBuffer.h"

#include "macros.h"
#include <GL/glew.h>

namespace JApp { namespace Renderer {

	TextureBuffer::TextureBuffer(const DataType dataType) {
		GL_CALL(glGenBuffers(1, &m_bufferId));
		GL_CALL(glBindBuffer(GL_TEXTURE_BUFFER, m_bufferId));
		GL_CALL(glGenTextures(1, &m_textureId));
		GL_CALL(glBindBuffer(GL_TEXTURE_BUFFER, 0));

		switch (dataType) {

		case FLOAT:
			m_dataType = GL_R32F;
			break;
		case VEC2:
			m_dataType = GL_RG32F;
			break;
		case VEC3:
			m_dataType = GL_RGB32F;
			break;
		case VEC4:
			m_dataType = GL_RGBA32F;
			break;
		default: ASSERT(false);
		}
	}

	TextureBuffer::TextureBuffer(float* data, const unsigned int size, const DataType dataType)
		: TextureBuffer(dataType) {
		GL_CALL(glBindBuffer(GL_TEXTURE_BUFFER, m_bufferId));
		GL_CALL(glBufferData(GL_TEXTURE_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW));
		GL_CALL(glBindBuffer(GL_TEXTURE_BUFFER, 0));
	}

	TextureBuffer::~TextureBuffer() {
		GL_CALL(glDeleteBuffers(1, &m_bufferId));
		GL_CALL(glDeleteTextures(1, &m_textureId));
	}

	void TextureBuffer::setData(float* data, const unsigned int size) const {
		GL_CALL(glBindBuffer(GL_TEXTURE_BUFFER, m_bufferId));
		GL_CALL(glBufferData(GL_TEXTURE_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW));
		GL_CALL(glBindBuffer(GL_TEXTURE_BUFFER, 0));
	}

	float* TextureBuffer::getDataPointer() const {
		GL_CALL(glBindBuffer(GL_TEXTURE_BUFFER, m_bufferId));
		GL_CALL(return (float*)glMapBuffer(GL_TEXTURE_BUFFER, GL_WRITE_ONLY));
	}

	void TextureBuffer::freeDataPointer() {
		GL_CALL(glUnmapBuffer(GL_TEXTURE_BUFFER));
	}

	void TextureBuffer::bind(const unsigned int slot) const {
		ASSERT(slot != 0);
		GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
		GL_CALL(glBindTexture(GL_TEXTURE_BUFFER, m_textureId));
		GL_CALL(glTexBuffer(GL_TEXTURE_BUFFER, m_dataType, m_bufferId));
	}

	void TextureBuffer::unbind() const {
		GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
	}
}}
