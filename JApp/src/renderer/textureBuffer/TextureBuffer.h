#pragma once

class TextureBuffer {
	unsigned int m_textureId, m_bufferId;
public:
	TextureBuffer();
	~TextureBuffer();
	void setData(float* data, unsigned int width, unsigned int height);
	void bind(unsigned int slot = 0) const;
	void unbind() const;
};
