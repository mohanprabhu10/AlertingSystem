#include <gtest/gtest.h>
#include "../../RulesBasedAlertingSystem/DeviceRepository.h"

namespace RulesBasedAlertingSystem {
	namespace Test {
		namespace Unit {

			class DeviceRepositoryTest : public ::testing::Test
			{

			};

			TEST_F(DeviceRepositoryTest, newDeviceRegister)
			{

				DeviceRepository deviceRepo(true);

				Device device;
				device.deviceId = "Temperature";
				device.validInputRange = { 0,100 };
				device.limits.push_back({ {0,50}, Normal, "Normal state" });
				device.limits.push_back({ {50,100}, Critical, "Critical State" });

				EXPECT_EQ(true, deviceRepo.registerNew(device));
				EXPECT_EQ(false, deviceRepo.registerNew(device));
				EXPECT_EQ(device.deviceId, deviceRepo.read("Temperature").deviceId);

				device.deviceId = "Pressure";
				device.validInputRange = { 0,50 };
				device.limits.push_back({ {0,25}, Warning, "Warning state" });
				device.limits.push_back({ {25, 50}, Critical, "Critical State" });

				EXPECT_EQ(true, deviceRepo.registerNew(device));
			}


			TEST_F(DeviceRepositoryTest, updateDevice)
			{

				DeviceRepository deviceRepo(true);

				Device device;
				device.deviceId = "Temperature";
				device.validInputRange = { 0,100 };
				device.limits.push_back({ {0,30}, Normal, "Normal state" });
				device.limits.push_back({ {30,100}, Critical, "Critical State" });

				EXPECT_EQ(true, deviceRepo.update(device));
				EXPECT_EQ(device.deviceId, deviceRepo.read("Temperature").deviceId);
				device.deviceId = "Phi";
				EXPECT_EQ(false, deviceRepo.update(device));
				
			}



			TEST_F(DeviceRepositoryTest, readDevice)
			{
				DeviceRepository deviceRepo(true);
				Device device;
				device.deviceId = "Temperature";
				EXPECT_EQ(device.deviceId, deviceRepo.read("Temperature").deviceId);
				device.deviceId = "";
				EXPECT_EQ(device.deviceId, deviceRepo.read("Temp").deviceId);

				EXPECT_EQ(2, deviceRepo.readAll().size());


			}

			TEST_F(DeviceRepositoryTest, CheckDeviceId)
			{

				DeviceRepository deviceRepo(true);
				EXPECT_EQ(true, deviceRepo.checkDeviceExist("Temperature"));
				EXPECT_EQ(false, deviceRepo.checkDeviceExist(""));
				
			}



			TEST_F(DeviceRepositoryTest, deletePatient)
			{

				DeviceRepository deviceRepo(true);
				EXPECT_EQ(true, deviceRepo.remove("Temperature"));
				EXPECT_EQ(false, deviceRepo.remove("Temperature"));
				EXPECT_EQ(true, deviceRepo.remove("Pressure"));

			}

		}
	}
}