
#include"EventManager.h"
#include"Task.h"
uint32_t millis() {
	return now;
}
uint32_t now = 0;

template<int i>
TaskStatus genFun() {
	printf("[%d]: %d\n", millis(),i); 
	return TaskStatus::NORMAL;
}
int a = 1;
void simularIR() {
	if (a == 1 && millis() >= 1000)
	{
		EventManager.happen_event(EventSlot::ir, 1);
		a++;
	}

	if (a == 2 && millis() >= 1500)
	{
		EventManager.happen_event(EventSlot::ir, 0);
		a++;
	}
}

int main()
{
	EventManager.slot_register(EventSlot::ir, 2);
	Task s;
	EventManager.slot_register(EventSlot::ir, 2);
	s.delay(100, genFun<1>)
		.delay(200, genFun<2>)
		.event<int>(EventSlot::ir, [](int v)->TaskStatus
	{
		printf("[%d]: ir,value:%d\n", millis(), v);
		return TaskStatus::NORMAL;
	})
		.delay(200, genFun<3>)
		.event<int>(EventSlot::ir, [](int v)->TaskStatus
	{
		printf("[%d]: ir,value:%d\n", millis(), v);
		return TaskStatus::BREAK;
	})
		.delay(200, genFun<4>);

	while (true)
	{
		simularIR();
		s.progress();

		now++;
		if (now > 3000)
			break;
	}
	return 0;
}