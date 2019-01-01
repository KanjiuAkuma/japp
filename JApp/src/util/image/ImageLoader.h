#pragma once
#include <string>
#include <thread>

namespace JApp {

	class ImageLoader {
	private:
		std::string m_path;
		unsigned char* m_image = nullptr;
		int m_imageWidth = 0, m_imageHeight = 0, m_bitsPerPixel = 0;
		bool m_isFinished = false;
		std::thread* m_thread = nullptr;
	public:
		explicit ImageLoader(const std::string& path);
		~ImageLoader();

		void start();
		void load();
		void join() const;

		bool isFinished() const;

		unsigned char* getImage() const;
		int getImageWidth() const;
		int getImageHeight() const;
		int getBitsPerPixel() const;

	};

}
