#pragma once
#include "../../RulesBasedAlertingSystem/IPatientRepository.h"

namespace RulesBasedAlertingSystem
{
	namespace Test
	{
		namespace Unit
		{
			class MockPatientRepo : public IPatientRepository
			{
			public:
				MockPatientRepo();
				bool checkPatientExists(std::string patientId) override;
				bool registerNew(Patient patient) override;
				bool update(Patient patient) override;
				bool remove(std::string patientId) override;
				Patient read(std::string patientID) override;
				std::vector<Patient> readAll() override;
				std::map<std::string, Patient> patientList;
			};
		}
	}
}