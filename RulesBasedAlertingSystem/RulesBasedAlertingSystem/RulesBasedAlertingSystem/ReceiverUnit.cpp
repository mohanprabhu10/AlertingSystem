#include "ReceiverUnit.h"
#include "json11.hpp"

namespace RulesBasedAlertingSystem
{
	ReceiverUnit::ReceiverUnit(SharedQueue &queue, std::map<std::string, Patient> &map, IInputOutputUnit &inOut ) : m_queue(queue), m_map(map), m_inOut(inOut)
	{
	}

	void ReceiverUnit::inputProcess() const
	{
		bool loopControl;
		do
		{
			std::string input = m_inOut.readVitals();
			loopControl = input.empty();
			if (!loopControl)
			{
				/*m_inOut.display("enqueued");*/
				PatientVitals vitals;
				if(unboxInput(input, vitals))
				{
					m_queue.enqueue(vitals);
					//m_inOut.display(vitals.patientId);
				}
					
				loopControl = true;
			}
		} while (loopControl);
	}

	bool ReceiverUnit::unboxInput(const std::string& input, PatientVitals &vitals) const
	{
		json11::Json object = json11::Json::parse(input, std::string("Input not recieved"));

		if(object["patientId"].is_string())
			vitals.patientId = object["patientId"].string_value();
		else
		{
			m_inOut.display("Patient ID not provided");
			return false;
		}
		auto devs = m_map[vitals.patientId].devices;
		for (auto i = devs.begin(); i != devs.end(); i++)
		{
			Vitals temp;
			temp.deviceId = i->first;
			if (object[i->first].is_null())
			{
				m_inOut.display("Device Not Registered : ");
				return false;
			}
			else
			{
				if (object[i->first].is_number())
				{
					temp.value = object[i->first].number_value();
					vitals.vitals.push_back(temp);
					continue;
				}
				m_inOut.display("Device Value Not Acceptable, Device ID : "+ temp.deviceId);
				return false;
			}
		}
		return true;
	}
}
