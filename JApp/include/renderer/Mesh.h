#pragma once

#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"
#include "renderer/VertexBufferLayout.h"
#include "renderer/IndexBuffer.h"

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
