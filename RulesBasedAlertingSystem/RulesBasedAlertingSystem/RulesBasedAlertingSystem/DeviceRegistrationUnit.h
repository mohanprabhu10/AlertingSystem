#pragma once
#include "IDeviceRepository.h"
#include "IInputOutputUnit.h"
#include <string>

namespace RulesBasedAlertingSystem
{

	class DeviceRegistrationUnit
	{
		void updateRegisteredDevices();   
		void readAllRegisteredDevices();
		void readRegisteredDevice();
		void deleteRegisteredDevice();
		void registerDevice();
		bool operationInDeviceRegistration(int operation);
		std::string getEnumTypeName(int);

	public:		
		DeviceRegistrationUnit(IDeviceRepository &deviceRepo, IInputOutputUnit &inOut);
		void readInput();
		std::vector<Limits> getLimits(Range range);
		Range getValidLimitsRange();
		std::string getMessage();
		Type getTypeOfRange();

	private:
		IDeviceRepository &m_deviceRepository;
		IInputOutputUnit &m_inOut;
	};
}
