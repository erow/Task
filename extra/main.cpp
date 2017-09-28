#include "stdafx.h"

#include"EventManager.h"
#include"TimeSequence.h"
uint32_t millis() {
	return now;
}
uint32_t now = 0;
int main()
{
	EventManager.slot_register(EventSlot::ir, 2);
	int value;

	TimeSequence s;
	s.delay(1, []() {printf("[%d]: 1\n", millis()); })
		.delay(2, []() {printf("[%d]: 3\n", millis()); })
		.event<int>(EventSlot::ir, [](int v) {printf("[%d]: fun2,value:%d\n", millis(), v); })
		.delay(2, []() {printf("[%d]: 5\n", millis()); });
	while (true)
	{
		s.check();
		now++;
		if(now>10)
			EventManager.happen_event(EventSlot::ir, 2);
	}
	return 0;
}