#pragma once

class TextureBuffer {
	unsigned int m_rendererId, m_buffId;
public:
	TextureBuffer(float* data, unsigned int size);
	~TextureBuffer();
	void bind(unsigned int slot = 0) const;
	void unbind() const;
};
