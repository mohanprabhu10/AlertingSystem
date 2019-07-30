#include "PatientRegistrationUnit.h"
#include "AlertingSystemModes.h"

namespace RulesBasedAlertingSystem
{
	PatientRegistrationUnit::PatientRegistrationUnit(IPatientRepository &patientRepo, IDeviceRepository &deviceRepo, IInputOutputUnit &inOut) : m_patientRepo(patientRepo), m_deviceRepo(deviceRepo), m_inOut(inOut)
	{
	}
	void PatientRegistrationUnit::readInput()
	{
		generateDeviceList();
		bool loopControl;
		do
		{
			std::string input = m_inOut.readInput("Select \n1.New Patient Registration   \n2.Update Registered Patient  \n3.Delete Registered Patient \n4.Read Patient using Patient ID  \n5.Read All Patients  \n6.Exit");
			try
			{
				loopControl = operationInPatientRegistration(stoi(input));
			}
			catch (...)
			{
				m_inOut.display("Invalid input.  Try again... ");
			}
			m_inOut.pause();

			m_inOut.clearScreen();
		} while (loopControl);
	}
	void PatientRegistrationUnit::generateDeviceList()
	{
		auto deviceList = m_deviceRepo.readAll();
		for (auto i = deviceList.begin(); i != deviceList.end(); i++)
		{
			m_deviceList.insert({ i->deviceId, *i });
		}
	}

	bool PatientRegistrationUnit::registerNewDevice(Patient &patient, std::string menu)
	{
		bool loopControl;
		menu.append("Enter Device ID : \nAvailable Devices are :\n");
		for (auto i = m_deviceList.begin(); i != m_deviceList.end(); i++)
		{
			menu.append(i->first + "\n");
		}
		menu.append("0 to exit...\n");
		std::string deviceID = m_inOut.readInput(menu);
		if (deviceID == "0")
			loopControl = false;
		else if (m_deviceList.find(deviceID) == m_deviceList.end())
		{
			m_inOut.display("Device Does not exist. Try Again\n");
			loopControl = true;
		}
		else if (patient.devices.find(deviceID) != patient.devices.end())
		{
			m_inOut.display("Device Already registered. Try Again\n");
			loopControl = true;
		}
		else
		{
			loopControl = true;
			auto device = registerDevice(deviceID);
			patient.devices.insert({ device.deviceId,device });
		}
		return loopControl;
	}

	bool PatientRegistrationUnit::updateDevice(Patient &patient, std::string menu)
	{
		bool loopControl;
		menu.append("Enter Device ID : \nAvailable Devices are :\n");
		for (auto i = m_deviceList.begin(); i != m_deviceList.end(); i++)
		{
			menu.append(i->first + "\n");
		}
		menu.append("0 to exit...\n");
		std::string deviceID = m_inOut.readInput(menu);
		if (stoi(deviceID) == 0)
			loopControl = false;
		else if (m_deviceList.find(deviceID) == m_deviceList.end())
		{
			m_inOut.display("Device Does not exist. Try Again\n");
			loopControl = true;
		}
		else if (patient.devices.find(deviceID) == patient.devices.end())
		{
			m_inOut.display("Device Not registered. Try Again\n");
			loopControl = true;
		}
		else
		{
			loopControl = true;
			patient.devices.erase(deviceID);
			auto device = registerDevice(deviceID);
			patient.devices.insert({ device.deviceId,device });
		}
		return loopControl;
	}

	void PatientRegistrationUnit::updateRegisteredPatients()
	{
		std::string patientID = m_inOut.readInput("Enter Patient ID : ");
		if (!m_patientRepo.checkPatientExists(patientID))
		{
			m_inOut.display("Patient doesn't exist");
			return;
		}
		else
		{
			Patient patient = m_patientRepo.read(patientID);
			bool loopControl;
			std::string menu;
			do
			{
				std::string input = m_inOut.readInput("1. Register New Device \n2. Update Registered Device \nAny other key to exit..");
				if (input == "1")
					loopControl = registerNewDevice(patient, menu);
				else if (input == "2")
				{
					loopControl = updateDevice(patient, menu);
				}
				else
				{
					loopControl = false;
				}
			}
			while (loopControl);
			m_patientRepo.update(patient);
		}
	}
	void PatientRegistrationUnit::readAllRegisteredPatients()
	{
		auto patients = m_patientRepo.readAll();
		if (patients.size() == 0)
		{
			m_inOut.display("No Patient found");
			return;
		}
		for (auto i = patients.begin(); i != patients.end(); i++)
			m_inOut.display(i->toString());
	}
	void PatientRegistrationUnit::readRegisteredPatients()
	{
		std::string patientId = m_inOut.readInput("Enter Patient ID");
		Patient patient = m_patientRepo.read(patientId);
		if (patient.patientId == "")
		{
			m_inOut.display("Patient Id not found");
		}
		else
		{
			m_inOut.display(patient.toString());
		}
	}
	void PatientRegistrationUnit::deleteRegisteredPatient()
	{
		std::string patientId = m_inOut.readInput("Enter Patient ID");
		if (m_patientRepo.remove(patientId))
			m_inOut.display("Removal Successful");
		else
			m_inOut.display("RemovalUnsuccessful");
	}
	void PatientRegistrationUnit::registerPatient()
	{
		Patient newPatient;
		newPatient.patientId = m_inOut.readInput("Enter Patient ID : ");
		if (m_patientRepo.checkPatientExists(newPatient.patientId))
		{
			m_inOut.criticalAlert("Patient Id already Exists");
			return;
		}
		bool loopControl;
		do
		{
			std::string menu;
			menu.append("Enter Device ID : \nRegistered Devices are :\n");
			for (auto i = m_deviceList.begin(); i != m_deviceList.end(); i++)
			{
				menu.append(i->first + "\n");
			}
			menu.append("0 to exit...\n");
			std::string deviceID = m_inOut.readInput(menu);
			if (deviceID == "0")
				loopControl = false;
			else if (m_deviceList.find(deviceID) == m_deviceList.end())
			{
				m_inOut.criticalAlert("Device Does not exist. Try Again\n");
				loopControl = true;
			}
			else if (newPatient.devices.find(deviceID) != newPatient.devices.end())
			{
				m_inOut.criticalAlert("Device Already registered. Try Again\n");
				loopControl = true;
			}
			else
			{
				loopControl = true;
				auto device = registerDevice(deviceID);
				newPatient.devices.insert({ device.deviceId,device });
			}

		}
		while (loopControl);
		m_patientRepo.registerNew(newPatient);
	}

	Device PatientRegistrationUnit::registerDevice(std::string deviceID)
	{
		Device newDevice;
		newDevice.deviceId = deviceID;
		std::string input = m_inOut.readInput("Do you want to set custom ranges for the device?\n(y/n)\n");
		if (input == "y" || input == "Y")
		{
			DeviceRegistrationUnit device(m_deviceRepo, m_inOut);
			newDevice.validInputRange = device.getValidLimitsRange();
			newDevice.limits = device.getLimits(newDevice.validInputRange);
			return newDevice;
		}
			return m_deviceList[deviceID];
	}
	bool PatientRegistrationUnit::operationInPatientRegistration(int operation)
	{
		switch (operation)
		{
		case 1:registerPatient();
			break;
		case 2:updateRegisteredPatients();
			break;
		case 3:deleteRegisteredPatient();
			break;
		case 4:readRegisteredPatients();
			break;
		case 5:readAllRegisteredPatients();
			break;
		case 6:
			return false;
		default:
			m_inOut.criticalAlert("Invalid input.  Try again... ");
			break;
		}
		return true;
	}
}