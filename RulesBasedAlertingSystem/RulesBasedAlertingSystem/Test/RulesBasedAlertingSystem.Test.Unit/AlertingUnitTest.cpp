#include "gtest\gtest.h"
#include "../../RulesBasedAlertingSystem/AlertingUnit.h"
#include "../../RulesBasedAlertingSystem/ConsoleInputOutput.h"
#include "MockPatientRepo.h"
#include<thread>
#include<string>
#include "MockInputOutput.h"

namespace RulesBasedAlertingSystem
{
	namespace Test
	{
		namespace Unit
		{
			class AlertingUnitTest : public ::testing::Test
			{

			};

			TEST_F(AlertingUnitTest, AllAlertsTest)
			{
				MockPatientRepo patRepo;
				std::map<std::string, Patient> patlist;
				auto pats = patRepo.readAll();
				for (auto i = pats.begin(); i != pats.end(); i++)
					patlist.insert({ i->patientId, *i });
				MockInputOutput inOut;
				AlertingUnit alerting(patlist, inOut);
				PatientVitals vitals;
				vitals.patientId = "11";
				vitals.vitals.push_back({ "100", 30 });
				vitals.vitals.push_back({ "200", 60 });
				vitals.vitals.push_back({ "300", 90 });
				alerting.checkLimits(vitals);
				ASSERT_NE(inOut.critical.size(), 0);
				ASSERT_NE(inOut.warning.size(), 0);
			}

			TEST_F(AlertingUnitTest, MultipleVitalsTest)
			{
				MockPatientRepo patRepo;
				std::map<std::string, Patient> patlist;
				auto pats = patRepo.readAll();
				for (auto i = pats.begin(); i != pats.end(); i++)
					patlist.insert({ i->patientId, *i });
				MockInputOutput inOut;
				AlertingUnit alerting(patlist, inOut);
				PatientVitals vitals;
				vitals.patientId = "11";
				vitals.vitals.push_back({ "100", 30 });
				vitals.vitals.push_back({ "200", 60 });
				vitals.vitals.push_back({ "300", 90 });
				alerting.checkLimits(vitals);
				ASSERT_NE(inOut.critical.size(), 0);
				ASSERT_NE(inOut.warning.size(), 0);
				vitals.patientId = "22";
				vitals.vitals.push_back({ "100", 90 });
				vitals.vitals.push_back({ "200", 60 });
				vitals.vitals.push_back({ "300", 30 });
				alerting.checkLimits(vitals);
				ASSERT_NE(inOut.critical.size(), 1);
				ASSERT_NE(inOut.warning.size(), 1);
				vitals.patientId = "33";
				vitals.vitals.push_back({ "100", 60 });
				vitals.vitals.push_back({ "200", 30 });
				vitals.vitals.push_back({ "300", 90 });
				alerting.checkLimits(vitals);
				ASSERT_NE(inOut.critical.size(), 2);
				ASSERT_NE(inOut.warning.size(), 2);
			}
		}
	}
}
