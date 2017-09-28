#ifndef EVENT_MANAGER
#define EVENT_MANAGER
#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include<queue>
enum class EventSlot
{
	ir,
	endofevent//don't edit this
};

class EventManagerClass
{
	
public:
	std::queue<void*> slots[int(EventSlot::endofevent)];
	int slot_length[int(EventSlot::endofevent)];
	bool slot_register(EventSlot slot, int length);
	template<typename T>
	bool happen_event(EventSlot slot, T value)
	{
		if (slots[int(slot)].size() >= slot_length[int(slot)])
			return false;
		slots[int(slot)].push(new T(value));
		return true;
	}

	template<typename T>
	bool poll_event(EventSlot slot, T& value)
	{
		if (slots[int(slot)].empty())
			return false;
		
		T* p = (T*)slots[int(slot)].front();
		slots[int(slot)].pop();
		value = *p;
		delete p;
		return true;
	}
	EventManagerClass();
	~EventManagerClass();
};


extern EventManagerClass EventManager;
#endif // EVENT_MANAGER