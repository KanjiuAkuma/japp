#pragma once

#include <GL/glew.h>

class TextureBuffer {
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
	void freeDataPointer();
	void bind(unsigned int slot = 0) const;
	void unbind() const;
};
