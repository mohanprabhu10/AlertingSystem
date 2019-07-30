#pragma once
#include "IInputOutputUnit.h"
#include "PatientVitals.h"
#include "Patient.h"
#include "SharedQueue.h"
#include <map>

namespace RulesBasedAlertingSystem
{
	class ReceiverUnit
	{
	public:
		ReceiverUnit(SharedQueue &queue, std::map<std::string, Patient> &map, IInputOutputUnit &inOut);
		void inputProcess() const;
	private:
		bool unboxInput(const std::string &input, PatientVitals &vitals)const;
	private:
		SharedQueue &m_queue;
		std::map<std::string, Patient> &m_map;
		IInputOutputUnit &m_inOut;
	};
}