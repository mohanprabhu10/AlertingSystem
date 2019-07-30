#pragma once
#include <string>
#include <vector>

namespace RulesBasedAlertingSystem
{
	struct Vitals
	{
		std::string deviceId;
		double value;
	};

	struct PatientVitals
	{
		std::string patientId;
		std::vector<Vitals> vitals;
	};

}
