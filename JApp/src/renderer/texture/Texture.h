#pragma once

#include <string>

namespace JApp { namespace Renderer {

	class Texture {
	private:
		unsigned int m_RendererID;
		explicit Texture(unsigned char* image, int width, int height);
		explicit Texture(float* data, int width, int height);
	public:
		~Texture();

		void bind(unsigned int slot = 0) const;
		void unbind() const;

		static Texture* fromFile(const std::string& path);
		static Texture* fromValues(unsigned char* image, int width, int height);
		static Texture* fromValues(float* data, int width, int height);
	};
}}
