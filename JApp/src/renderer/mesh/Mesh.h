#pragma once

#include "renderer/vertexArray/VertexArray.h"
#include "renderer/vertexBuffer/VertexBuffer.h"
#include "renderer/vertexBufferLayout/VertexBufferLayout.h"
#include "renderer/indexBuffer/IndexBuffer.h"

namespace JApp { namespace Renderer {

	struct Mesh {
		VertexArray* va;
		VertexBuffer* vb;
		VertexBufferLayout* vbl;
		IndexBuffer* ib;

		Mesh(VertexArray* va, VertexBuffer* vb, VertexBufferLayout* vbl, IndexBuffer* ib);
		~Mesh();

		void bind() const;
		void unbind() const;

		unsigned int getVertexCount() const;

	};

}}
