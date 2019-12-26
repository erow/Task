#ifndef TIME_SEQUENCE
#define TIME_SEQUENCE

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include<list>
#include<vector>

#include"EventManager.h"
#include"Functions.h"

class Task
{
private:
	struct trigger_pair
	{
		uint16_t m_delay;
		Function* callback;
	};
	std::vector<trigger_pair> sequence;
	uint32_t m_lasttime = 0;
	int m_cur= 0;
public:
	Task();
	~Task();
	float progress();
	Task& delay(uint16_t ms, NoneFun call);
	Task& delay(uint16_t ms, Function call);
	template<typename T>
	Task& event(EventSlot slot, OneFun<T> call) {
		sequence.push_back(trigger_pair{ 0,new OneParam<T>(slot,call) });
		return *this;
	}
};


#endif // !TIME_SEQUENCE
