#include "AlertingSystemModes.h"
#include "DeviceRegistrationUnit.h"
#include "PatientRegistrationUnit.h"
#include "AlertProcessingUnit.h"

#include<iostream>
#include<string>
#include "ConsoleInputOutput.h"
#include "PatientRepository.h"
#include "VitalsRepository.h"
#include "DeviceRepository.h"
using namespace std;

namespace RulesBasedAlertingSystem {

	AlertingSystemModes::AlertingSystemModes()
	{
		m_deviceRepository.reset(new DeviceRepository());
		m_patientRepository.reset(new PatientRepository);
		m_vitalsRepository.reset(new VitalsRepository);
		m_inOut.reset(new ConsoleInputOutput());
	}

	void AlertingSystemModes::displayModes()
	{

		
		string modeInput;
		do
		{
			modeInput = m_inOut->readInput("Select \n1.Device Registration   \n2.Patient Registration  \n3.Patient Monitor  \n4.Exit");
			try
			{
				selectMode(stoi(modeInput));
				m_inOut->pause();
				m_inOut->clearScreen();
			}
			catch(...)
			{
				m_inOut->criticalAlert("Invalid input.  Try again... ");
			}
			
		} while (true);
	}


	void AlertingSystemModes::selectMode(int mode)
	{
		DeviceRegistrationUnit deviceRegistration(*m_deviceRepository, *m_inOut);
		PatientRegistrationUnit patientRegistration(*m_patientRepository, *m_deviceRepository, *m_inOut);
		AlertProcessingUnit alertProcessingUnit(*m_patientRepository, *m_vitalsRepository, *m_inOut);

		switch (mode)
		{
		case 1:
			deviceRegistration.readInput();
			break; 
		case 2:
			patientRegistration.readInput();
			break;
		case 3:
			alertProcessingUnit.initialize();
			break;
		case 4:
			exit(0);
		default:
			m_inOut->criticalAlert("Invalid input.  Try again... ");
			break;
		}
	}


}
