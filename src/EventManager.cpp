// EventManagerClass.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "EventManager.h"

EventManagerClass EventManager;

bool EventManagerClass::slot_register(EventSlot slot, int length)
{
	if(length<1|| slot_length[int(slot)])
		return false;
	slot_length[int(slot)]=(length);
	return true;
}

EventManagerClass::EventManagerClass()
{
}


EventManagerClass::~EventManagerClass()
{
}



