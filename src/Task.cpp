#include "Task.h"

Task::Task()
{
}

Task::~Task()
{
	for (int i = 0; i < sequence.size(); i++)
		delete sequence[i].callback;
}

float Task::progress()
{
	if (m_cur >= sequence.size())
		return 1.0f;
	if (millis() >= m_lasttime + sequence[m_cur].m_delay) {
		switch ((*sequence[m_cur].callback)())
		{
		case TaskStatus::BREAK:
			m_cur = sequence.size();
			m_lasttime = millis();
			break;
		case TaskStatus::CONTINUE:
			m_cur=0;
			m_lasttime = millis();
			break;
		case TaskStatus::NORMAL:
			m_cur++;
			m_lasttime = millis();
			break;
		case TaskStatus::PAUSE:
			break;
		default:
			break;
		}
	}
	return float(m_cur) / sequence.size();
}

Task & Task::delay(uint16_t ms, NoneFun call)
{
	sequence.push_back(trigger_pair{ ms,new NoneParam(call)});
	return *this;
}

Task & Task::delay(uint16_t ms, Function call)
{
	sequence.push_back(trigger_pair{ ms,new Function(call )});
	return *this;
}
