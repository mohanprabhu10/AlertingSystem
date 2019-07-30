#include "gtest\gtest.h"
#include "../../RulesBasedAlertingSystem/VitalsRepository.h"
namespace RulesBasedAlertingSystem
{
	namespace Test
	{
		namespace Unit
		{
			class VitalsRepositoryTest : public ::testing::Test
			{

			};

			TEST_F(VitalsRepositoryTest, ReadWriteVitalsTest)
			{
				VitalsRepository vitalsRepo(true); //true is for testing mode
				PatientVitals vitals;
				vitals.patientId = "111";
				vitals.vitals.push_back({ "1", 12.1 });
				EXPECT_EQ(vitalsRepo.writeVitals(vitals),true);
				auto returnVal = vitalsRepo.readVitals("111");
				EXPECT_EQ(returnVal.empty(), false);
				EXPECT_EQ("1", returnVal[0].vitals[0].deviceId);
				EXPECT_EQ("111", returnVal[0].patientId);
				EXPECT_EQ(12.1, returnVal[0].vitals[0].value);

			}
			TEST_F(VitalsRepositoryTest, ReadinvalidVitalsTest)
			{
				VitalsRepository vitalsRepo(true); //true is for testing mode
				PatientVitals vitals;
				vitals.patientId = "112";
				vitals.vitals.push_back({ "1", 12.1 });
				auto retVal = vitalsRepo.readVitals("113");
				EXPECT_EQ(retVal.empty(), true);
			}

		}
	}
}