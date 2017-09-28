#include "TimeSequence.h"



TimeSequence::TimeSequence()
{
	
}


TimeSequence::~TimeSequence()
{
	for (int i = 0; i < sequence.size(); i++)
		delete sequence[i].callback;
}

void TimeSequence::check()
{
	if (m_cur >= sequence.size())
		return;
	if (millis() >= m_lasttime + sequence[m_cur].m_delay) {
		
		if ((*sequence[m_cur].callback)() >= 1.0f)
		{
			m_cur++;
			m_lasttime = millis();
		}
	}
}

TimeSequence & TimeSequence::delay(uint16_t ms, NoneFun call)
{
	sequence.push_back(trigger_pair{ ms,new NoneParam(call)});
	return *this;
}

TimeSequence & TimeSequence::delay(uint16_t ms, Function call)
{
	sequence.push_back(trigger_pair{ ms,new Function(call )});
	return *this;
}
