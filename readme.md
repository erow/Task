If you are in trouble with timer,or you want to use event-driven programming.I hope this library can help you.

# Aim
A lightweight but powerful implementation of  linear single-tasking supporting:
1. Time-driven
2. Event-driven
3. Tasking control
4. Cross-platform
---
## Time-driven
Simply use `delay`.
 
``
s.delay(100,f1).delay(200, f2)
``

## Event-driven
First of all, write all events needed on `EventSlot`.
```
enum class EventSlot
{
	ir,//add event slot by yourself
	endofevent//don't edit this
};
```  

Then **register** a slot, and indicate the maximum length of slot queue.`EventManager.slot_register(EventSlot::ir, 2);`,

It's easy to **send** and **recv** a event.And you can put a param to the receiver

`.event<int>(EventSlot::ir, f3);` << `EventManager.happen_event(EventSlot::ir, somevalue);`.

If you put too much event to the slot, the latest will be drop.
**Be careful of the type in f3**

## Tasking control
The callback function return control code which is one of:
```
enum TaskStatus {
	NORMAL,
	PAUSE,
	CONTINUE,
	BREAK
};
```
If you **pause** a task, it won't execute the next mission on the task list.  
if you **continue** a task, it will rerun from the beginning.  
if you **break** a task, it will stop.

And `progress` will return value from 0 to 1.


Finally you must put progress in your loop.

## Example

```
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
/*
[100]: 1
[300]: 2
[300]: ir,value:1
[600]: 3
[600]: ir,value:0
[1100]: 1
[1300]: 2
[1300]: ir,value:1
[1600]: 3
[1600]: ir,value:0
[2100]: 1
[2300]: 2
[2300]: ir,value:0
[2600]: 3
[2600]: ir,value:1
[3100]: 1
[3300]: 2
[3300]: ir,value:0
[3600]: 3
[3600]: ir,value:1
*/
```



