#pragma once
#include <sstream>

namespace JApp {

	class EventFormat {
	private:
		std::stringstream stream;
		int m_elements = 0;
	public:

		explicit EventFormat(const std::string& type);

		std::string str() const;

		template<typename T>
		void append(const std::string& name, T value) {
			if (!m_elements++) {
				stream << ":";
			}
			else {
				stream << ",";
			}
			stream << " " << name << "=" << value;
		}
	};

}