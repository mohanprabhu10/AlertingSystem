#pragma once
#include "../../RulesBasedAlertingSystem/IDeviceRepository.h"
#include <map>

namespace RulesBasedAlertingSystem
{
	namespace Test
	{
		namespace Unit
		{
			class MockDeviceRepo : public IDeviceRepository
			{
			public:
				MockDeviceRepo();
				bool checkDeviceExist(std::string deviceId) override;
				bool registerNew(Device device) override;
				bool update(Device device) override;
				bool remove(std::string patientId) override;
				Device read(std::string deviceID) override;
				std::vector<Device> readAll() override;

				std::map<std::string, Device> m_devicelist;
			};
		}
	}
}
