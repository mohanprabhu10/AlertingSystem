#pragma once
#include "Device.h"
#include "Patient.h"
#include "PatientVitals.h"

namespace RulesBasedAlertingSystem 
{
	class IPatientRepository
	{
	public: 
		virtual ~IPatientRepository() {}
		virtual bool checkPatientExists(std::string patientId) = 0;
		virtual bool registerNew(Patient patient) = 0;
		virtual bool update(Patient patient) = 0;
		virtual bool remove(std::string patientId) = 0;
		virtual Patient read(std::string patientID) = 0;
		virtual std::vector<Patient> readAll() = 0;
	};
}