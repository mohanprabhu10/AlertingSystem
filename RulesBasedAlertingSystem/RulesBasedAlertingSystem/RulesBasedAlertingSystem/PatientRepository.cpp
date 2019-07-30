#include "PatientRepository.h"
#include <fstream>
#include <string>
#include <sstream>
using namespace std;


namespace RulesBasedAlertingSystem 
{

	PatientRepository::PatientRepository(bool temp)
	{
		if (!temp)
			m_patientRepositoryPath = "Database\\PatientRepo.txt";
		else
			m_patientRepositoryPath = "..\\..\\..\\TestDatabase\\PatientRepo.txt";
	}

	bool PatientRepository::checkPatientExists(string patientId)
	{

		string line;
		ifstream infile;
		infile.open(m_patientRepositoryPath);

		if (infile.is_open())
		{
			while (getline(infile, line))
			{
				if (line.substr(0, line.find("/")) == patientId)
				{
					return true;
				}
			}
			infile.close();
		}
		return false;

	}


	int PatientRepository::getPatientLineNumber(string patientId)
	{
		int lineNum = 0;
		string line;
		ifstream infile;
		infile.open(m_patientRepositoryPath);

		if (infile.is_open())
		{


			while (getline(infile, line)) {
				lineNum++;

				if (line.substr(0, line.find("/")) == patientId)
				{
					return lineNum;
				}
			}
			infile.close();
		}
		return 0;
	}

	string PatientRepository::patientToString(Patient patient)
	{

		try
		{
			string patientText;

			patientText.append(patient.patientId);
			patientText.append("/");
			patientText.append(to_string(patient.devices.size()));
			patientText.append("/");


			map<string, Device>::iterator itr;
			for (itr = patient.devices.begin(); itr != patient.devices.end(); ++itr)
			{

				patientText.append(itr->first);
				patientText.append("/");

				patientText.append(itr->second.deviceId);
				patientText.append("/");
				patientText.append(to_string(itr->second.validInputRange.min));
				patientText.append("/");
				patientText.append(to_string(itr->second.validInputRange.max));
				patientText.append("/");
				patientText.append(to_string(itr->second.limits.size()));

				for (int i = 0; i < itr->second.limits.size(); i++)
				{
					patientText.append("/");
					patientText.append(to_string(itr->second.limits[i].range.min));
					patientText.append("/");
					patientText.append(to_string(itr->second.limits[i].range.max));
					patientText.append("/");
					patientText.append(to_string(itr->second.limits[i].type));
					patientText.append("/");
					patientText.append(itr->second.limits[i].message);

				}

				patientText.append("/");
			}

			
			return patientText;
		}
		catch (...)
		{
			return "";
		}
	}

	Patient PatientRepository::stringToPatient(std::string line)
	{
		try
		{

			stringstream strstream(line);
			string segment;
			vector<string> patientVector;
			string deviceId;
			int vectorIndex = 2;
			int limitIndex;
			Patient patient;
			Device device;
			Limits limits;

			patientVector.clear();
			while (getline(strstream, segment, '/'))
			{
				patientVector.push_back(segment);
			}
			patient.patientId = patientVector[0];

			for (int i=0;i<stoi(patientVector[1]);i++)
			{
				deviceId = patientVector[vectorIndex++];
				device.deviceId = patientVector[vectorIndex++];
				device.validInputRange.min = stod(patientVector[vectorIndex++]);
				device.validInputRange.max = stod(patientVector[vectorIndex++]);
				limitIndex = vectorIndex++;
				for (int i = 0; i < stoi(patientVector[limitIndex]); i++)
				{
					limits.range.min = stod(patientVector[vectorIndex++]);
					limits.range.max = stod(patientVector[vectorIndex++]);
					limits.type = Type(stoi(patientVector[vectorIndex++]));
					limits.message = patientVector[vectorIndex++];
					device.limits.push_back(limits);
				}

				patient.devices.insert(pair<string, Device>(deviceId, device));
			}

			return patient;

		}
		catch (...)
		{
			Patient nullPatient;
			return nullPatient;
		}
	}

	bool PatientRepository::registerNew(Patient patient)
	{
		if (checkPatientExists(patient.patientId))
		{
			return false;
		}
		string patienttext = patientToString(patient);

		if (patienttext == "")
		{
			return false;
		}


		ofstream outFile;

		outFile.open(m_patientRepositoryPath, ios::app);
		if (!outFile)
		{
			return false;
		}
		else
		{
			outFile << patienttext << std::endl;
		}
		outFile.close();
		return true;
	}


	bool PatientRepository::update(Patient patient)
	{

		if (!remove(patient.patientId))
		{
			return false;
		}

		if (!registerNew(patient))
		{
			return false;
		}
		return true;
	}

	Patient PatientRepository::read(std::string patientId)
	{
		string line;
		ifstream infile;
		infile.open(m_patientRepositoryPath);

		if (infile.is_open())
		{


			while (getline(infile, line))
			{

				if (line.substr(0, line.find("/")) == patientId)
				{
					return stringToPatient(line);
				}
			}
			infile.close();
		}

		Patient patient;
		return patient;
	}

	vector<Patient> PatientRepository::readAll()
	{
		string line;
		ifstream infile;
		infile.open(m_patientRepositoryPath);

		vector<Patient> allPatient;
		allPatient.clear();

		Patient patient;

		if (infile.is_open())
		{


			while (getline(infile, line))
			{

				patient = stringToPatient(line);
				if (patient.patientId != "")
				{
					allPatient.push_back(patient);
				}

			}
			infile.close();
		}

		return allPatient;
	}

	bool PatientRepository::remove(string patientId)
	{
		int lineNumDel = getPatientLineNumber(patientId);
		if (lineNumDel == 0)
		{
			return false;
		}

		string line;

		ifstream infile(m_patientRepositoryPath);
		if (!infile)
		{
			return false;
		}

		ofstream ofs;
		ofs.open("temp.txt", ofstream::out);
		int line_no = 0;
		while (getline(infile, line))
		{
			line_no++;
			if (line_no != lineNumDel)
				ofs << line << endl;
		}

		ofs.close();
		infile.close();
		std::remove(m_patientRepositoryPath.c_str());
		std::rename("temp.txt", m_patientRepositoryPath.c_str());
		return true;
	}
}