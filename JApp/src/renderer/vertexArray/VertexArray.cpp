#include "VertexArray.h"

#include "macros.h"
#include <GL/glew.h>



VertexArray::VertexArray()
{
	GL_CALL(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
	GL_CALL(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::addBuffer(const VertexBuffer* vb, const VertexBufferLayout* layout)
{
	bind();
	vb->bind();
	const auto& elements = layout->getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GL_CALL(glEnableVertexAttribArray(i));
		GL_CALL(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout->getStride(), (const void*) offset));

		offset += element.count * VertexBufferElement::getSizeOfType(element.type);
	}
}

void VertexArray::bind() const
{
	GL_CALL(glBindVertexArray(m_RendererID));
}

void VertexArray::unbind() const
{
	GL_CALL(glBindVertexArray(0));
}
