#include "MockDeviceRepo.h"

namespace RulesBasedAlertingSystem
{
	namespace Test
	{
		namespace Unit
		{

			MockDeviceRepo::MockDeviceRepo()
			{
				for (int i = 1; i < 4; i++)
				{
					Device dev;
					dev.deviceId = std::to_string((i * 100));
					dev.validInputRange = { 0,100 };
					for(int j = 0; j < 3; j++)
					{
						Limits lim;
						if (j == 0) lim.range = { 0,50 };
						else if (j == 1) lim.range = { 50,75 };
						else lim.range = { 75, 100 };
						lim.type = Type(j + 1);
						lim.message = lim.type;
						dev.limits.push_back(lim);
					}
					m_devicelist.insert({ dev.deviceId, dev });
				}
			}

			bool MockDeviceRepo::checkDeviceExist(std::string deviceId)
			{
				return (deviceId == "100" || deviceId == "200" || deviceId == "300");
				
			}

			bool MockDeviceRepo::registerNew(Device device)
			{
				m_devicelist.insert({ device.deviceId, device });
				return true;
			}

			bool MockDeviceRepo::update(Device device)
			{
				if (m_devicelist.find(device.deviceId)!=m_devicelist.end())
				{
					m_devicelist[device.deviceId] = device;
					return true;
				}
				return false;

			}

			bool MockDeviceRepo::remove(std::string patientId)
			{
				if (m_devicelist.find(patientId) != m_devicelist.end())
				{
					m_devicelist.erase(patientId);
					return true;
				}
				return false;
			}

			Device MockDeviceRepo::read(std::string deviceID)
			{
				if (m_devicelist.find(deviceID) != m_devicelist.end())
				{
					return m_devicelist[deviceID];
				}
				return {};
			}

			std::vector<Device> MockDeviceRepo::readAll()
			{
				std::vector<Device> devList;
				for (auto i = m_devicelist.begin(); i != m_devicelist.end(); i++)
					devList.push_back(i->second);
				return devList;
			}
		}
	}
}
