// RulesBasedAlertingSystem.Host.cpp : Defines the entry point for the console application.
//

#include "../RulesBasedAlertingSystem/AlertingSystemModes.h"
#include "../RulesBasedAlertingSystem/ReceiverUnit.h"
#include "../RulesBasedAlertingSystem/AlertProcessingUnit.h"
#include "../RulesBasedAlertingSystem/ConsoleInputOutput.h"
#include "../RulesBasedAlertingSystem/VitalsRepository.h"
#include "../RulesBasedAlertingSystem/PatientRepository.h"
#include "../RulesBasedAlertingSystem/DeviceRepository.h"
#include <iostream>

int main()
{
	std::string line;
	RulesBasedAlertingSystem::AlertingSystemModes modes;
	modes.displayModes();
	//while (std::getline(std::cin, line)) // read from std::cin
	//{
	//	// show that it arrived
	//	
	//}
    return 0;
}

