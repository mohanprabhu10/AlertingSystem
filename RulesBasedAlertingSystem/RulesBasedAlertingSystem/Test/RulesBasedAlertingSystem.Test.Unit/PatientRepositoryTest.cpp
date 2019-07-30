#include <gtest/gtest.h>
#include "../../RulesBasedAlertingSystem/PatientRepository.h"

namespace RulesBasedAlertingSystem {
	namespace Test {
		namespace Unit {

			class PatientRepositoryTest : public ::testing::Test
			{

			};

			TEST_F(PatientRepositoryTest, newPatientRegister)
			{
				
				PatientRepository patientRepo(true);

				Patient patient;

				patient.patientId = "Philips";
				Device device;
				device.deviceId = "Temperature";
				device.validInputRange = { 0,100 };
				device.limits.push_back({ {0,50}, Normal, "Normal state" });
				device.limits.push_back({ {50,100}, Critical, "Critical State" });

				patient.devices.insert({ device.deviceId, device });

				device.deviceId = "Pressure";
				device.validInputRange = { 0,50 };
				device.limits.push_back({ {0,25}, Warning, "Warning state" });
				device.limits.push_back({ {25, 50}, Critical, "Critical State" });

				patient.devices.insert({ device.deviceId, device });

				EXPECT_EQ(true,patientRepo.registerNew(patient));
				EXPECT_EQ(false, patientRepo.registerNew(patient));
				EXPECT_EQ(patient.patientId, patientRepo.read("Philips").patientId);

				patient.patientId = "PIC";
				EXPECT_EQ(true, patientRepo.registerNew(patient));
				

				
			}


			TEST_F(PatientRepositoryTest, updatePatient)
			{

				PatientRepository patientRepo(true);

				Patient patient;

				patient.patientId = "Philips";
				Device device;
				device.deviceId = "Temperature";
				device.validInputRange = { 0,100 };
				device.limits.push_back({ {0,50}, Normal, "Normal state" });
				device.limits.push_back({ {50,100}, Critical, "Critical State" });

				patient.devices.insert({ device.deviceId, device });

				EXPECT_EQ(true, patientRepo.update(patient));
				patient.patientId = "Phi";
				EXPECT_EQ(false, patientRepo.update(patient));
				EXPECT_EQ(1, patientRepo.read("Philips").devices.size());
			}



			TEST_F(PatientRepositoryTest, readPatient)
			{
				PatientRepository patientRepo(true);
				Patient patient;
				patient.patientId = "Philips";
				EXPECT_EQ(patient.patientId, patientRepo.read("Philips").patientId);
				EXPECT_EQ(2, patientRepo.readAll().size());


			}

			TEST_F(PatientRepositoryTest, CheckPatientId)
			{

				PatientRepository patientRepo(true);
				EXPECT_EQ(true, patientRepo.checkPatientExists("Philips"));
				EXPECT_EQ(false, patientRepo.checkPatientExists(""));
				EXPECT_EQ(false, patientRepo.remove("PICA"));
			}

			TEST_F(PatientRepositoryTest, deletePatient)
			{

				PatientRepository patientRepo(true);
				EXPECT_EQ(true, patientRepo.remove("Philips"));
				EXPECT_EQ(false, patientRepo.remove("Philips"));
				EXPECT_EQ(true, patientRepo.remove("PIC"));
				
			}

		}	
	}
}