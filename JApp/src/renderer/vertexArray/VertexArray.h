#pragma once

#include "renderer/vertexBuffer/VertexBuffer.h"
#include "renderer/vertexBufferLayout/VertexBufferLayout.h"

class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void addBuffer(const VertexBuffer* vb, const VertexBufferLayout* layout);
	void bind() const;
	void unbind() const;
};
