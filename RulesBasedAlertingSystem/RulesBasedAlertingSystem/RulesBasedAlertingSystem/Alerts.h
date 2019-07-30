#pragma once
#include <string>

namespace RulesBasedAlertingSystem
{
	struct Alerts
	{
		std::string deviceId;
		double value;
		std::string message;

		std::string toString()
		{
			return std::string("Device ID : " + deviceId + "\nValue : " + std::to_string(value) + "\nMessage : " + message);
		}
	};
}
