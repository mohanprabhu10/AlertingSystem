#pragma once
#include "IVitalsRepository.h"

namespace RulesBasedAlertingSystem 
{
	class VitalsRepository : public IVitalsRepository
	{
	public:
		VitalsRepository(bool temp = false);
		bool writeVitals(PatientVitals vitals) override;
		std::vector<PatientVitals> readVitals(std::string patientID) override;

	private:
		std::string vitalsToString(PatientVitals vitals);
		PatientVitals stringToVitals(std::string line);
	private:
		std::string m_vitalsRepositoryPath;
	};
}