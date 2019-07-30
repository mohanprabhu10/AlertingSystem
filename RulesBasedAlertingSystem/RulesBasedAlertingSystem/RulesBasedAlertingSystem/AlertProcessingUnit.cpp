#include "AlertProcessingUnit.h"
#include "ReceiverUnit.h"


namespace RulesBasedAlertingSystem
{
	AlertProcessingUnit::AlertProcessingUnit(IPatientRepository &patientRepo, IVitalsRepository &vitalsRepo, IInputOutputUnit &inOut) : m_patientRepository(patientRepo) , m_vitalsRepository(vitalsRepo), m_inOut(inOut)
	{
	}

	void AlertProcessingUnit::initialize()
	{
		//Create map
		std::map<std::string, Patient> patientMap;
		auto patientsList = m_patientRepository.readAll();
		for (auto i = patientsList.begin(); i != patientsList.end(); i++)
		{
			patientMap.insert({ i->patientId, {i->patientId, i->devices} });
			//m_inOut.display("INIT"+ i->toString());
		}
		//Create a new thread for reciever unit
		ReceiverUnit receiver(m_queue, patientMap, m_inOut);
		std::thread inputThread(&ReceiverUnit::inputProcess, receiver);
		//Initialize Alert and create its object
		AlertingUnit alertingUnit(patientMap, m_inOut);
		//Call process
		process(alertingUnit);
		inputThread.join();
	}

	void AlertProcessingUnit::process(AlertingUnit &alertingUnit)
	{
		do
		{
			if (!m_queue.isEmpty())
			{
				PatientVitals vitalsInput = m_queue.dequeue();
				//m_inOut.display("dequeued");
				//m_inOut.display(vitalsInput.patientId);
				//Alerting System
				alertingUnit.checkLimits(vitalsInput);
				//Storage System
				m_vitalsRepository.writeVitals(vitalsInput);
			}
		} while (true);
	}

}