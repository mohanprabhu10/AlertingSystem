#include "AlertingUnit.h"

namespace RulesBasedAlertingSystem
{
	AlertingUnit::AlertingUnit(std::map< std::string, Patient> &patientList, IInputOutputUnit &inOut) : m_patientList(patientList) , m_inOut(inOut)
	{
		for (auto i = m_patientList.begin(); i != m_patientList.end(); i++)
		{
			m_criticalMap.insert({ i->first, std::vector<Alerts>() });
			m_warningMap.insert({ i->first, std::vector<Alerts>() });
		}
	}

	bool AlertingUnit::compare(double min, double max, double val)
	{
		return (val >= min && val < max);
	}

	void AlertingUnit::alertUser()
	{
		//m_inOut.display("Alerting");
		//Add clear screen here...
		m_inOut.clearScreen();
		m_inOut.criticalAlert("\tCritical");
		m_inOut.criticalAlert("************************");
		m_inOut.criticalAlert("************************");
		for (auto itr = m_criticalMap.begin(); itr != m_criticalMap.end(); itr++)
		{
			//Fix for displaying the vector
			if (itr->second.empty())
				continue;
			m_inOut.criticalAlert("Patient ID : " + itr->first + "\n");
			//do the same fix as above
			for each (Alerts var in itr->second)
			{
				m_inOut.criticalAlert(var.toString());
			}
			m_inOut.warningAlert("----------------------");
		}
		m_inOut.warningAlert("\tWarning");
		m_inOut.warningAlert("************************");
		m_inOut.warningAlert("************************");
		for (auto itr = m_warningMap.begin(); itr != m_warningMap.end(); itr++)
		{
			if (itr->second.empty())
				continue;
			m_inOut.warningAlert("Patient ID : " + itr->first+"\n");
			//do the same fix as above
			for each (Alerts var in itr->second)
			{
				m_inOut.warningAlert(var.toString());
			}
			m_inOut.warningAlert("----------------------");
		}
	}


	void AlertingUnit::checkLimits(PatientVitals vitals)
	{
		//m_inOut.display("checkingLimits");
		//m_inOut.display(vitals.patientId);
		std::vector<Alerts> criticalVector;
		std::vector<Alerts> warningVector;
		//for (auto i = m_patientList.begin(); i != m_patientList.end(); i++)
		//	m_inOut.display(i->second.toString());
		Patient patient = m_patientList[vitals.patientId];
		//m_inOut.display(patient.toString());
		for (auto i = vitals.vitals.begin(); i != vitals.vitals.end(); ++i)
		{
			//m_inOut.display("stuck here");
			if (!compare(patient.devices[i->deviceId].validInputRange.min, patient.devices[i->deviceId].validInputRange.max, i->value))
			{
				criticalVector.push_back({ i->deviceId, i->value, "Device Malfunction : Value out of valid input range." });
				continue;
			}
			auto limit = patient.devices[i->deviceId].limits;
			auto j = limit.begin();
			bool loopControl = true;
			do
			{
				if (compare(j->range.min, j->range.max, i->value))
				{
					switch (j->type)
					{
					case Critical:
						criticalVector.push_back({ i->deviceId, i->value, j->message });
						loopControl = false;
						break;
					case Warning:
						warningVector.push_back({ i->deviceId, i->value, j->message });
						loopControl = false;
						break;
					case Normal:
						loopControl = false;
						break;
					default:
						criticalVector.push_back({ i->deviceId, i->value, "Unexpected Error : Undefined Type" });
						loopControl = false;
						break;
					}
				}
				j++;
			} while (loopControl);
			m_criticalMap.erase(vitals.patientId);
			m_criticalMap.insert({ vitals.patientId, criticalVector });
			m_warningMap.erase(vitals.patientId);
			m_warningMap.insert({ vitals.patientId, warningVector });
			alertUser();
		}

	}
}