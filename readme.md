Use time and event to manager program.And my major aim is non blocking.

---
## feature
1. You can use `delay` to control which function should be run. 
``
s.delay(100, []()    {printf("[%d]: now is 100 \n", millis()); })
		.delay(200, []() {printf("[%d]: now is 300 \n", millis()); })
``

2. If you need event.
You should **register**first `EventManager.slot_register(EventSlot::ir, 2);`,
```
enum class EventSlot
{
	ir,//add event slot by yourself
	endofevent//don't edit this
};
``` 
Then some code will wait for your event `.event<int>(EventSlot::ir, [](int v) {printf("[%d]: ir range :%d\n", millis(), v); });`
Someone need to create event `EventManager.happen_event(EventSlot::ir, rand());`.


