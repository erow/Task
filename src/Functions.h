#pragma once
#include"EventManager.h"
typedef void(*NoneFun)();
class Function {
public:
	virtual float operator()() {
		return 1.0f;
	};//·µ»Ø½ø¶È
};
class NoneParam :public Function {
public:
	
	NoneFun m_function;
	NoneParam(NoneFun fun) { m_function = fun; };
	float operator()() {
		m_function();
		return 1.f;
	}
};
template<class T>
class OneParam :public Function {
private:
	typedef void(*OneFun)(T);
	EventSlot m_slot;
	OneFun m_fun;

public:
	OneParam(EventSlot slot, OneFun function) {
		m_slot = slot;
		m_fun = function;
	}
	float operator()() {
		T value;
		if (EventManager.poll_event(EventSlot::ir, value)) {
			m_fun(value);
			return 1.0f;
		}
		return 0;
	}
};