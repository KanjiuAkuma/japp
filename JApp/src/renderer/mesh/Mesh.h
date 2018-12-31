#pragma once

#include "renderer/vertexArray/VertexArray.h"
#include "renderer/vertexBuffer/VertexBuffer.h"
#include "renderer/vertexBufferLayout/VertexBufferLayout.h"
#include "renderer/indexBuffer/IndexBuffer.h"

struct Mesh {
	VertexArray* va;
	VertexBuffer* vb;
	VertexBufferLayout* vbl;
	IndexBuffer* ib;

	Mesh(VertexArray* va, VertexBuffer* vb, VertexBufferLayout* vbl, IndexBuffer* ib);
	~Mesh();

	void bind() const;

};
