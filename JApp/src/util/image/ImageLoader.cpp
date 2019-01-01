#include "ImageLoader.h"

#include "stb/stb_image.h"

namespace JApp {

	ImageLoader::ImageLoader(const std::string& path) : m_path(path) {}
	ImageLoader::~ImageLoader() {
		stbi_image_free(m_image);
	}

	void ImageLoader::start() {
		m_thread = new std::thread(&ImageLoader::load, this);
	}

	void ImageLoader::load() {
		// load image
		stbi_set_flip_vertically_on_load(1);
		m_image = stbi_load(m_path.c_str(), &m_imageWidth, &m_imageHeight, &m_bitsPerPixel, 4);
		m_isFinished = true;
	}

	void ImageLoader::join() const {
		if (m_thread && !m_isFinished) {
			m_thread->join();
		}
	}

	bool ImageLoader::isFinished() const {
		return m_isFinished;
	}

	unsigned char* ImageLoader::getImage() const {
		return m_image;
	}

	int ImageLoader::getImageWidth() const {
		return m_imageWidth;
	}

	int ImageLoader::getImageHeight() const {
		return m_imageHeight;
	}

	int ImageLoader::getBitsPerPixel() const {
		return m_bitsPerPixel;
	}

}