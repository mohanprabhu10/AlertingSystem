#pragma once
#include "Alerts.h"
#include "Patient.h"
#include "PatientVitals.h"
#include "IPatientRepository.h"
#include "IInputOutputUnit.h"

namespace RulesBasedAlertingSystem
{
	class AlertingUnit
	{

	public: 
		AlertingUnit(std::map< std::string, Patient> &patientList, IInputOutputUnit &inOut);
		void checkLimits(PatientVitals vitals);
	private:
		void alertUser();
		bool compare(double min, double max, double value);
	private:
		std::map< std::string, std::vector<Alerts> > m_criticalMap;
		std::map< std::string, std::vector<Alerts> > m_warningMap;
		std::map< std::string, Patient> m_patientList;
		IInputOutputUnit &m_inOut;
	};
}