#pragma once

#include <GL/glew.h>

namespace JApp { namespace Renderer {

	class TextureBuffer {
		unsigned int m_slot;
		unsigned int m_textureId, m_bufferId;
		GLenum m_dataType;
	public:

		enum DataType {
			FLOAT,
			VEC2,
			VEC3,
			VEC4,
		};

		explicit TextureBuffer(DataType dataType);
		explicit TextureBuffer(float* data, unsigned int size, DataType dataType);
		~TextureBuffer();
		void setData(float* data, unsigned int size) const;
		float* getDataPointer() const;
		void freeDataPointer() const;
		unsigned int getSlot() const;
		void bind() const;
		void unbind() const;
	};


}}
