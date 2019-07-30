#include "VitalsRepository.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

namespace RulesBasedAlertingSystem
{

	VitalsRepository::VitalsRepository(bool temp)
	{
		if (!temp)
		{
			m_vitalsRepositoryPath = "Database\\";
		}
		else
		{
			m_vitalsRepositoryPath = "..\\..\\..\\TestDatabase\\";
		}
	}

	bool VitalsRepository::writeVitals(PatientVitals vitals)
	{
		if (m_vitalsRepositoryPath.find(".txt") == std::string::npos)
			m_vitalsRepositoryPath.append(vitals.patientId+".txt");
		std::string line = vitalsToString(vitals);
		std::ofstream file;
		file.open(m_vitalsRepositoryPath, std::ios::app);
		if (file.is_open())
		{
			file << line << std::endl;
			file.close();
			return true;
		}
		return false;
	}

	std::vector<PatientVitals> VitalsRepository::readVitals(std::string patientID)
	{
		if (m_vitalsRepositoryPath.find(".txt") == std::string::npos)
			m_vitalsRepositoryPath.append(patientID + ".txt");
		std::vector<PatientVitals> allVitals;
		std::string line;
		std::ifstream file;
		file.open(m_vitalsRepositoryPath);
		if (file.is_open())
		{
			while (std::getline(file, line))
			{
				allVitals.push_back(stringToVitals(line));
			}
			file.close();
			return allVitals;
		}
		return std::vector<PatientVitals>();
	}

	std::string VitalsRepository::vitalsToString(PatientVitals vitals)
	{
		std::string vitalsString;
		vitalsString.append(vitals.patientId + "/");
		for (auto i = vitals.vitals.begin(); i != vitals.vitals.end(); i++)
			vitalsString.append(i->deviceId + "/" + std::to_string(i->value) + "/");
		return vitalsString;
	}

	PatientVitals VitalsRepository::stringToVitals(std::string line)
	{
		std::stringstream strstream(line);
		std::string segment;
		std::vector<std::string> vitalsVector;

		while (getline(strstream, segment, '/'))
		{
			vitalsVector.push_back(segment);
		}
		PatientVitals vitals;
		vitals.patientId = vitalsVector[0];
		for (size_t i = 1; i < vitalsVector.size(); i++)
		{
			Vitals info;
			info.deviceId = vitalsVector[i];
			i++;
			info.value = std::stod(vitalsVector[i]);
			vitals.vitals.push_back(info);
		}
		return vitals;
	}
}