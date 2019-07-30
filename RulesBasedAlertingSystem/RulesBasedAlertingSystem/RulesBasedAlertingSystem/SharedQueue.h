#pragma once
#include <queue>
#include <mutex>
#include "PatientVitals.h"

namespace RulesBasedAlertingSystem
{
	class SharedQueue
	{
	public:
		void enqueue(const PatientVitals &vitals);
		PatientVitals dequeue();
		bool isEmpty();

	private:
		std::mutex m_lock;
		std::queue<PatientVitals> m_queue;
	};
}