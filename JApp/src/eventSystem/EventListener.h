#pragma once

template<class T>
class EventListener {
public:
	virtual ~EventListener() = default;
	virtual bool process(T* e) = 0;
};
