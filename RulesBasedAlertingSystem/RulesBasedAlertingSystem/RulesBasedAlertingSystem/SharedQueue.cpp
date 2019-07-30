#include "SharedQueue.h"

namespace RulesBasedAlertingSystem
{
	bool SharedQueue::isEmpty()
	{
		return m_queue.empty();
	}

	void SharedQueue::enqueue(const PatientVitals& vitals)
	{
		std::lock_guard<std::mutex> locker(m_lock);
		m_queue.push(vitals);
	}

	PatientVitals SharedQueue::dequeue()
	{
		std::lock_guard<std::mutex> locker(m_lock);
		PatientVitals vitals = m_queue.front();
		m_queue.pop();
		return vitals;
	}


}