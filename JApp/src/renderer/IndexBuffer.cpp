#include "renderer/IndexBuffer.h"

#include "macros.h"
#include <GL/glew.h>

namespace JApp { namespace Renderer {

	IndexBuffer::IndexBuffer(const unsigned int* data, const unsigned int count)
		: m_count(count) {
		ASSERT(sizeof(unsigned int) == sizeof(GLuint));
		GL_CALL(glGenBuffers(1, &m_RendererID));
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
		GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
	}

	IndexBuffer::~IndexBuffer() {
		GL_CALL(glDeleteBuffers(1, &m_RendererID));
	}

	void IndexBuffer::bind() const {
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	}

	void IndexBuffer::unbind() const {
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	unsigned IndexBuffer::getCount() {
		return m_count;
	}

}}
