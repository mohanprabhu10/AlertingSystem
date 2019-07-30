#pragma once
#include "Device.h"
#include "PatientVitals.h"

namespace RulesBasedAlertingSystem
{
	class IDeviceRepository
	{
	public: 
		virtual ~IDeviceRepository() {}
		virtual bool checkDeviceExist(std::string deviceId) = 0;
		virtual bool registerNew(Device device) = 0;
		virtual bool update(Device device) = 0;
		virtual bool remove(std::string patientId) = 0;
		virtual Device read(std::string deviceID) = 0;
		virtual std::vector<Device> readAll() = 0;
	};
}