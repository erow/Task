#include <ArduinoSTL.h>
#include <EventManager.h>
#include "Task.h"
static FILE uartout = { 0 };
static int uart_putchar(char c, FILE *stream)
{
	Serial.write(c);
	return 0;
}

Task s;

template<unsigned long i>
TaskStatus genFun() {
	printf("[%d]: ", millis());
	Serial.println(i);
	return TaskStatus::NORMAL;
}

TaskStatus printEvent(int v)
{
	printf("[%d]: ir,value:", millis());
	Serial.println(v);
	return TaskStatus::NORMAL;
}
void setup()
{
	pinMode(2, INPUT);
	// Start the UART
	Serial.begin(115200);

	// fill in the UART file descriptor with pointer to writer.
	fdev_setup_stream(&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE);

	// The uart is the standard output device STDOUT.
	stdout = &uartout;

	EventManager.slot_register(EventSlot::ir, 2);
	s.delay(100, genFun<1>)
		.delay(200, genFun<2>)
		.event<int>(EventSlot::ir, printEvent)
		.delay(300, genFun<3>)
		.event<int>(EventSlot::ir, printEvent)
		.delay(400, []() {return TaskStatus::CONTINUE; });

			
}

void checkIR() {
	static int last = 0;
	int v = digitalRead(2);
	if (v != last)
	{
		last = v;
		EventManager.happen_event(EventSlot::ir,v);
	}
}

int a = 1;
void simularIR() {
	if (a == 1 && (millis() % 500) == 0)
	{
		EventManager.happen_event(EventSlot::ir, 1);
		a++;
	}

	if (a == 2 && (millis() % 1000)==0)
	{
		EventManager.happen_event(EventSlot::ir, 0);
		a=1;
	}
}
void loop()
{
	//checkIR();
	simularIR();
	s.progress();
	
}
