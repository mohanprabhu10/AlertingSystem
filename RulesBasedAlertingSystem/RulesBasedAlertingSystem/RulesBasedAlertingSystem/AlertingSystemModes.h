#pragma once
#include <memory>
#include "IDeviceRepository.h"
#include "IPatientRepository.h"
#include "IVitalsRepository.h"
#include "IInputOutputUnit.h"


namespace RulesBasedAlertingSystem {

	class AlertingSystemModes
	{
		

	public:
		AlertingSystemModes();
		void displayModes();
	private:
		void selectMode(int mode);
	private:
		mutable std::unique_ptr<IDeviceRepository> m_deviceRepository;
		mutable std::unique_ptr<IPatientRepository> m_patientRepository;
		mutable std::unique_ptr<IVitalsRepository> m_vitalsRepository;
		mutable std::unique_ptr<IInputOutputUnit> m_inOut;
	};

}
