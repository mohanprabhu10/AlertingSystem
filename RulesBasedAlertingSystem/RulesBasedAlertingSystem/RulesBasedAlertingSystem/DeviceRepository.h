#pragma once
#include "IDeviceRepository.h"

namespace RulesBasedAlertingSystem 
{
	class DeviceRepository : public IDeviceRepository
	{
	public:
		DeviceRepository(bool temp = false);
		bool checkDeviceExist(std::string deviceId) override;
		bool remove(std::string deviceId) override; 
		bool registerNew(Device device) override;
		bool update(Device device) override;
		Device read(std::string deviceID) override;
		std::vector<Device> readAll() override;
	private:
		int getDeviceLineNumber(std::string deviceId);
		std::string deviceToString(Device device);
		Device stringToDevice(std::string line);
	private:
		std::string m_deviceRepositoryPath;
	};
}