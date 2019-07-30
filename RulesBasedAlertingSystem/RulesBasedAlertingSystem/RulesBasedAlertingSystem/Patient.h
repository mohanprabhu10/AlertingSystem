#pragma once
#include <string>
#include <map>
#include "Device.h"

namespace RulesBasedAlertingSystem {
	struct Patient
	{
		std::string patientId;
		std::map<std::string, Device> devices;

		std::string toString()
		{
			std::string output("Patient ID : " + patientId+"\nDevices : \n");
			for (auto i = devices.begin(); i != devices.end(); i++)
				output.append(i->second.toString() + "\n");
			return output;
		}
		
	};
}
