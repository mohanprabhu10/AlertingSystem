#include "IDeviceRepository.h"
#include "DeviceRepository.h"
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


namespace RulesBasedAlertingSystem {



	DeviceRepository::DeviceRepository(bool temp)
	{
		if (!temp)
			m_deviceRepositoryPath = "Database\\DeviceRepo.txt";
		else
			m_deviceRepositoryPath = "..\\..\\..\\TestDatabase\\DeviceRepo.txt";
	}

	bool DeviceRepository::checkDeviceExist(string deviceId)
	{
		string line;
		ifstream infile;
		infile.open(m_deviceRepositoryPath);

		if (infile.is_open())
		{
			while (getline(infile, line))
			{
				if (line.substr(0, line.find("/")) == deviceId)
				{
					return true;
				}
			}
			infile.close();
		}
		return false;

	}




	int  DeviceRepository::getDeviceLineNumber(string deviceID)
	{

		int lineNum = 0;
		string line;
		ifstream infile;
		infile.open(m_deviceRepositoryPath);

		if (infile.is_open())
		{

			
			while (getline(infile, line)) { 
				lineNum++;

				if (line.substr(0, line.find("/")) == deviceID)
				{
					return lineNum;
				}
			}
			infile.close();
		}
		return 0;
	

	}

	string DeviceRepository::deviceToString(Device device)
	{
		try
		{
			string devicetext;

			devicetext.append(device.deviceId);
			devicetext.append("/");
			devicetext.append(to_string(device.validInputRange.min));
			devicetext.append("/");
			devicetext.append(to_string(device.validInputRange.max));
			devicetext.append("/");
			devicetext.append(to_string(device.limits.size()));

			for (int i = 0; i < device.limits.size(); i++)
			{
				devicetext.append("/");
				devicetext.append(to_string(device.limits[i].range.min));
				devicetext.append("/");
				devicetext.append(to_string(device.limits[i].range.max));
				devicetext.append("/");
				devicetext.append(to_string(device.limits[i].type));
				devicetext.append("/");
				devicetext.append(device.limits[i].message);

			}

			devicetext.append("/");
			return devicetext;
		}
		catch (...)
		{
			return "";
		}

	}


	Device DeviceRepository::stringToDevice(std::string line)
	{
		try
		{

			stringstream strstream(line);
			string segment;
			vector<string> deviceVector;
			deviceVector.clear();

			while (getline(strstream, segment, '/'))
			{
				deviceVector.push_back(segment);
			}

			Device device;

			device.deviceId = deviceVector[0];
			device.validInputRange.min = stod(deviceVector[1]);
			device.validInputRange.max = stod(deviceVector[2]);

			Limits limits;

			int index = 4;
			for (int i = 0; i < stoi(deviceVector[3]); i++)
			{
				limits.range.min = stod(deviceVector[index++]);
				limits.range.max = stod(deviceVector[index++]);
				limits.type = Type(stoi(deviceVector[index++]));
				limits.message = deviceVector[index++];
				device.limits.push_back(limits);
			}

			return device;

		}
		catch (...)
		{
			Device nullDevice;
			return nullDevice;
		}


	}



	bool DeviceRepository::registerNew(Device device)
	{


		if (checkDeviceExist(device.deviceId))
		{
			return false;
		}
		string devicetext = deviceToString(device);

		if (devicetext=="")
		{
			return false;
		}


		ofstream outFile;

		outFile.open(m_deviceRepositoryPath, ios::app);
		if (!outFile) 
		{
			return false;
		}
		else
		{
			outFile << devicetext << std::endl;
		}
		outFile.close();
		return true;

	}
	bool DeviceRepository::update(Device device)
	{

		if (!remove(device.deviceId))
		{
			return false;
		}

		if (!registerNew(device))
		{
			return false;
		}
		return true;
	}
	Device DeviceRepository::read(std::string deviceID)
	{

		
		string line;
		ifstream infile;
		infile.open(m_deviceRepositoryPath);

		if (infile.is_open())
		{


			while (getline(infile, line))
			{

				if (line.substr(0, line.find("/"))==deviceID)
				{				
					return stringToDevice(line);
				}
			}
			infile.close();
		}

		Device device;
		return device;
	}
	std::vector<Device> DeviceRepository::readAll()
	{
		string line;
		ifstream infile;
		infile.open(m_deviceRepositoryPath);

		vector<Device> allDevices;
		allDevices.clear();

		Device device;

		if (infile.is_open())
		{
			while (getline(infile, line))
			{
				
				device = stringToDevice(line);
				if (device.deviceId != "")
				{
					allDevices.push_back(device);
				}
	 
			}
			infile.close();
		}

		return allDevices;
	}
	bool DeviceRepository::remove(std::string deviceId)
	{

		int lineNumDel = getDeviceLineNumber(deviceId);
		if (lineNumDel == 0)
		{
			return false;
		}

		string line;

		ifstream infile(m_deviceRepositoryPath);
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

		std::remove(m_deviceRepositoryPath.c_str());
		std::rename("temp.txt" , m_deviceRepositoryPath.c_str());
		
		
		return true;
	}
}


