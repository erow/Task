#include <ArduinoSTL.h>
#include <EventManager.h>
#include "TimeSequence.h"
static FILE uartout = { 0 };
static int uart_putchar(char c, FILE *stream)
{
	Serial.write(c);
	return 0;
}

TimeSequence s;
void setup()
{
	// Start the UART
	Serial.begin(115200);

	// fill in the UART file descriptor with pointer to writer.
	fdev_setup_stream(&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE);

	// The uart is the standard output device STDOUT.
	stdout = &uartout;

	EventManager.slot_register(EventSlot::ir, 2);
	s.delay(100, []()    {printf("[%d]: now is 100 \n", millis()); })
		.delay(200, []() {printf("[%d]: now is 300 \n", millis()); })
		.event<int>(EventSlot::ir, [](int v) {printf("[%d]: ir range :%d\n", millis(), v); })
		.delay(100, []() {printf("[%d]: 100ms after ir\n", millis()); })
		.event<int>(EventSlot::ir, [](int v) {printf("[%d]: ir range :%d\n", millis(), v); })
		.delay(100, []() {printf("[%d]: 100ms after ir\n", millis());
						  EventManager.happen_event(EventSlot::ir, rand()); })
		.event<int>(EventSlot::ir, [](int v) {printf("[%d]: ir range :%d\n", millis(), v); });
}

int a = 1;
void loop()
{
	s.check();
	if (a==1&&millis() >= 1000)
	{
		EventManager.happen_event(EventSlot::ir, rand());
		a++;
	}

	if (a == 2 && millis() >= 1500)
	{
		EventManager.happen_event(EventSlot::ir, rand());
		a++;
	}
}
