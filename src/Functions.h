#pragma once
#include"EventManager.h"

enum TaskStatus {
	NORMAL,
	PAUSE,
	CONTINUE,
	BREAK
};
typedef TaskStatus(*NoneFun)();
template<typename T>
using OneFun = TaskStatus(*)(T);
class Function {
public:
	virtual TaskStatus operator()() {
		return TaskStatus::NORMAL;
	};//return control code
};
class NoneParam :public Function {
public:
	
	NoneFun m_function;
	NoneParam(NoneFun fun) { m_function = fun; };
	TaskStatus operator()() {
		return m_function();
	}
};
template<class T>
class OneParam :public Function {
private:
	EventSlot m_slot;
	OneFun<T> m_fun;

public:
	OneParam(EventSlot slot, OneFun<T> function) {
		m_slot = slot;
		m_fun = function;
	}
	TaskStatus operator()() {
		T value;
		if (EventManager.poll_event(EventSlot::ir, value)) {
			return m_fun(value);
		}
		return PAUSE;
	}
};