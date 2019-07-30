#pragma once
#include "../../RulesBasedAlertingSystem/IVitalsRepository.h"

namespace RulesBasedAlertingSystem
{
	namespace Test
	{
		namespace Unit
		{
			class MockVitalsRepo : public IVitalsRepository
			{
			public:
				bool writeVitals(PatientVitals vitals) override;
				std::vector<PatientVitals> readVitals(std::string patientID) override;

				std::vector<PatientVitals> m_vitals;
			};
		}
	}
}