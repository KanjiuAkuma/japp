#pragma once

#include <string>
#include <forward_list>

namespace JApp { namespace Renderer {

	class Texture {
	private:
		inline static unsigned int MAX_SLOTS = 48;
		static std::forward_list<unsigned int>* generateFreeSlots();

		inline static std::forward_list<unsigned int>* s_freeSlots = generateFreeSlots();

		unsigned int m_rendererID, m_slot;
		explicit Texture(unsigned char* image, int width, int height);
		explicit Texture(float* data, int width, int height);

	public:
		~Texture();

		unsigned int getSlot() const;
		void bind() const;
		void unbind() const;

		static Texture* fromFile(const std::string& path);
		static Texture* fromValues(unsigned char* image, int width, int height);
		static Texture* fromValues(float* data, int width, int height);

		static unsigned int getFreeSlot();
		static void freeSlot(unsigned int slot);
	};
}}
