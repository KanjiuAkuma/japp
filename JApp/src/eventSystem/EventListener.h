#pragma once

namespace JApp {

	template<class T>
	class EventListener {
	public:
		virtual ~EventListener() = default;
		virtual bool process(T* e) = 0;
	};

}
