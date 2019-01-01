#pragma once

#include "renderer/VertexBuffer.h"
#include "renderer/VertexBufferLayout.h"

namespace JApp { namespace Renderer {

	class VertexArray {
	private:
		unsigned int m_RendererID;
	public:
		VertexArray();
		~VertexArray();

		void addBuffer(const VertexBuffer* vb, const VertexBufferLayout* layout);
		void bind() const;
		void unbind() const;
	};

}}
