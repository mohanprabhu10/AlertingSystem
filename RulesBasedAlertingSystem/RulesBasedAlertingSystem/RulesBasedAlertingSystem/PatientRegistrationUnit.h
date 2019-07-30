#pragma once
#include "Patient.h"
#include "IPatientRepository.h"
#include "IInputOutputUnit.h"
#include "DeviceRegistrationUnit.h"


namespace RulesBasedAlertingSystem
{
	class PatientRegistrationUnit
	{
	public:
		PatientRegistrationUnit(IPatientRepository &patientRepo, IDeviceRepository &deviceRepo, IInputOutputUnit &inOut);
		void readInput();
	private:
		void generateDeviceList();
		bool registerNewDevice(Patient &patient, std::string menu);
		bool updateDevice(Patient &patient, std::string menu);
		void updateRegisteredPatients();
		void readAllRegisteredPatients();
		void readRegisteredPatients();
		void deleteRegisteredPatient();
		void registerPatient();
		Device registerDevice(std::string deviceID);
		bool operationInPatientRegistration(int operation);
	private:
		IPatientRepository &m_patientRepo;
		IDeviceRepository &m_deviceRepo;
		IInputOutputUnit &m_inOut;
		std::map<std::string, Device> m_deviceList;

	};
}