#pragma once

#include "macros.h"
#include <GL/glew.h>

#include <vector>

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int getSizeOfType(const unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: return 4;
		default:
			ASSERT(false);
			return 0;
		}
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout()
		: m_Stride(0) {}

	template <typename T>
	void push(const unsigned int count)
	{
		ASSERT(false);
	}

	template<>
	void push<float>(const unsigned int count) {
		m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += VertexBufferElement::getSizeOfType(GL_FLOAT) * count;
	}

	std::vector<VertexBufferElement> getElements() const
	{
		return m_elements;
	}

	unsigned int getStride() const
	{
		return m_Stride;
	}
};
