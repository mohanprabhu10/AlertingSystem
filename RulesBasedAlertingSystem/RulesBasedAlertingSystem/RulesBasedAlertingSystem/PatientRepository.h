#pragma once
#include "IPatientRepository.h"


namespace RulesBasedAlertingSystem
{
	class PatientRepository : public IPatientRepository
	{
	public:
		PatientRepository(bool temp = false);
		bool checkPatientExists(std::string patientId) override;
		int getPatientLineNumber(std::string patientId);
		std::string patientToString(Patient patient);
		Patient stringToPatient(std::string line);
		bool remove(std::string patientId) override;
		bool registerNew(Patient patient) override;
		bool update(Patient patient) override;
		Patient read(std::string patientId) override;
		std::vector<Patient> readAll() override;
	private:
		std::string m_patientRepositoryPath;
	};
}