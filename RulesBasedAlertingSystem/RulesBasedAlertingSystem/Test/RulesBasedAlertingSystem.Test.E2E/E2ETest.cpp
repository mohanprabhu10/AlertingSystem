#include <gtest/gtest.h>
#include "../../RulesBasedAlertingSystem/DeviceRepository.h"
#include "../../RulesBasedAlertingSystem/Patient.h"
#include "../../RulesBasedAlertingSystem/DeviceRegistrationUnit.h"
#include "../RulesBasedAlertingSystem.Test.Unit/MockDeviceRepo.h"
#include "../RulesBasedAlertingSystem.Test.Unit/MockInputOutput.h"
#include "../RulesBasedAlertingSystem.Test.Unit/MockPatientRepo.h"
#include "../../RulesBasedAlertingSystem/AlertProcessingUnit.h"
#include "../RulesBasedAlertingSystem.Test.Unit/MockVitalsRepo.h"

namespace RulesBasedAlertingSystem {
	namespace Test {
		namespace E2E {

			class E2ETest : public ::testing::Test
			{

			};

			TEST_F(E2ETest, warningAlert)
			{
				Unit::MockDeviceRepo deviceRepo;
				Unit::MockInputOutput inOut;
				DeviceRegistrationUnit device(deviceRepo, inOut);
				Unit::MockPatientRepo patientRepo;
				Unit::MockVitalsRepo vitalsRepo;
				RulesBasedAlertingSystem::AlertProcessingUnit alertProcessing(patientRepo, vitalsRepo, inOut);

				alertProcessing.initialize();
				EXPECT_NE(inOut.warning.size(), 0);
			}

			TEST_F(E2ETest, criticalAlert)
			{
				Unit::MockDeviceRepo deviceRepo;
				Unit::MockInputOutput inOut;
				DeviceRegistrationUnit device(deviceRepo, inOut);
				Unit::MockPatientRepo patientRepo;
				Unit::MockVitalsRepo vitalsRepo;
				RulesBasedAlertingSystem::AlertProcessingUnit alertProcessing(patientRepo, vitalsRepo, inOut);

				alertProcessing.initialize();
				EXPECT_NE(inOut.warning.size(), 0);
			}
		}
	}
}
