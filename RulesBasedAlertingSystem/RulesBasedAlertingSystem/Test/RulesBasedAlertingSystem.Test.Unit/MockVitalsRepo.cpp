#include "MockVitalsRepo.h"

namespace RulesBasedAlertingSystem
{
	namespace Test
	{
		namespace Unit
		{
			bool RulesBasedAlertingSystem::Test::Unit::MockVitalsRepo::writeVitals(PatientVitals vitals)
			{
				m_vitals.push_back(vitals);
				return true;
			}

			std::vector<RulesBasedAlertingSystem::PatientVitals> RulesBasedAlertingSystem::Test::Unit::MockVitalsRepo::
				readVitals(std::string patientID)
			{
				return m_vitals;
			}
		}
	}
}