#include "MockPatientRepo.h"

namespace RulesBasedAlertingSystem
{
	namespace Test
	{
		namespace Unit
		{
			RulesBasedAlertingSystem::Test::Unit::MockPatientRepo::MockPatientRepo()
			{
				for (int i = 1; i < 4; i++)
				{
					Patient pat;
					pat.patientId = std::to_string(i) + std::to_string(i);
					for (int i = 1; i < 4; i++)
					{
						Device dev;
						dev.deviceId = std::to_string((i * 100));
						dev.validInputRange = { 0,100 };
						for (int j = 0; j < 3; j++)
						{
							Limits lim;
							if (j == 0) lim.range = { 0,50 };
							else if (j == 1) lim.range = { 50,75 };
							else lim.range = { 75, 100 };
							lim.type = Type(j);
							lim.message = lim.type;
							dev.limits.push_back(lim);
						}
						pat.devices.insert({ dev.deviceId, dev });
					}
					patientList.insert({ pat.patientId, pat });
				}
			}
			bool RulesBasedAlertingSystem::Test::Unit::MockPatientRepo::checkPatientExists(std::string patientId)
			{
				return (patientList.find(patientId) != patientList.end());
			}

			bool RulesBasedAlertingSystem::Test::Unit::MockPatientRepo::registerNew(Patient patient)
			{
				patientList.insert({ patient.patientId, patient });
				return true;
			}

			bool RulesBasedAlertingSystem::Test::Unit::MockPatientRepo::update(Patient patient)
			{
				if(patientList.find(patient.patientId) != patientList.end())
				{
					patientList[patient.patientId] = patient;
					return true;
				}
				return false;
			}

			bool RulesBasedAlertingSystem::Test::Unit::MockPatientRepo::remove(std::string patientId)
			{
				if (patientList.find(patientId) != patientList.end())
				{
					patientList.erase(patientId);
					return true;
				}
				return false;
			}

			RulesBasedAlertingSystem::Patient RulesBasedAlertingSystem::Test::Unit::MockPatientRepo::read(std::string patientID)
			{
				if (patientList.find(patientID) != patientList.end())
				{
					return patientList[patientID];
				}
				return{};
			}

			std::vector<RulesBasedAlertingSystem::Patient> RulesBasedAlertingSystem::Test::Unit::MockPatientRepo::readAll()
			{
				std::vector<Patient> patList;
				for (auto i = patientList.begin(); i != patientList.end(); i++)
					patList.push_back(i->second);
				return patList;
			}
		}
	}
}