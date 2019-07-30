#include "DeviceRegistrationUnit.h"
#include "AlertingSystemModes.h"
#include "IDeviceRepository.h"

#include "Device.h"
#include<string>
using namespace std;
namespace RulesBasedAlertingSystem
{
	DeviceRegistrationUnit::DeviceRegistrationUnit(IDeviceRepository &deviceRepo, IInputOutputUnit &inOut) : m_deviceRepository(deviceRepo), m_inOut(inOut)
	{
	}

	void DeviceRegistrationUnit::readInput()
	{
		bool loopControl;
		do
		{
			string input = m_inOut.readInput("Select \n1.New Device Registration   \n2.Update Registered Device  \n3.Delete Registered Device \n4.Read Device using DeviceID  \n5.Read All Devices  \n6.Exit");
			try
			{			
				loopControl = operationInDeviceRegistration(stoi(input));
			}
			catch (...)
			{
				m_inOut.criticalAlert("Invalid input.  Try again... ");
				loopControl = true;
			}
			m_inOut.pause();
			m_inOut.clearScreen();
		} while (loopControl);
	}

	bool DeviceRegistrationUnit::operationInDeviceRegistration(int operation)
	{
		switch (operation)
		{
		case 1:registerDevice();

			break;
		case 2:updateRegisteredDevices();
			break;
		case 3:deleteRegisteredDevice();
			break;
		case 4:readRegisteredDevice();
			break;
		case 5:readAllRegisteredDevices();
			break;
		case 6:
			return false;
		default:
			m_inOut.criticalAlert("Invalid input.  Try again... ");
			break;
		}
		return true;
	}

	Range DeviceRegistrationUnit::getValidLimitsRange()
	{
		Range range;
		bool validRangeFlag;
		string inputRange;
		//To check valid range
		do
		{
			validRangeFlag = true;
			inputRange = m_inOut.readInput("Enter valid Input Range for the Device\n Min Range : ");

			while (1)
			{
				try
				{
					range.min = stod(inputRange);
					break;
				}
				catch (...)
				{
					m_inOut.criticalAlert("Invalid input.  Try again... ");
					inputRange = m_inOut.readInput("");
				}
			}

			inputRange = m_inOut.readInput(" Max Range : ");

			while (1)
			{
				try
				{
					range.max = stod(inputRange);
					break;
				}
				catch (...)
				{
					m_inOut.criticalAlert("Invalid input.  Try again... ");
					inputRange = m_inOut.readInput("");
				}
			}

			if (range.min >= range.max)
			{
				
				m_inOut.criticalAlert("Invalid input.  Try again... ");
				validRangeFlag = false;
			}
		} while (!validRangeFlag);

		return range;
	}

	vector<Limits> DeviceRegistrationUnit::getLimits(Range range)
	{

		double max;
		vector<Limits> limits;
		limits.clear();
		Limits limit;
		bool validRangeFlag;
		string inputRange;
		

		double min = range.min;

		do {

			
			do {
				validRangeFlag = true;
				inputRange = m_inOut.readInput("Enter the  sub range starting from "+to_string(min)+" to ");
				while (1)
				{
					try
					{
						max = stod(inputRange);
						break;
					}
					catch (...)
					{
						m_inOut.criticalAlert("Invalid input.  Try again... ");
						inputRange = m_inOut.readInput("");
					}
				}


				if (max > range.max || max<=min)
				{
					m_inOut.criticalAlert("Invalid input.  Try again... ");
					validRangeFlag = false;
				}
			} while (!validRangeFlag);


			limit.range.min = min;
			limit.range.max = max;

			min = max;

			limit.type = getTypeOfRange();
			limit.message= getMessage();


		
			limits.push_back(limit);
			
		} while (max < range.max);

		return limits;
	}


	Type DeviceRegistrationUnit::getTypeOfRange()
	{
		bool validRangeFlag;
		Type type;
		int rangeType;
		do {

			validRangeFlag = true;


			string inputType = m_inOut.readInput("Enter type of Range . \n1.Normal  \n2.Warning  \n3.Critical");

			while (true)
			{
				try
				{
					rangeType = stoi(inputType);
					break;
				}
				catch (...)
				{
					m_inOut.criticalAlert("Invalid input.  Try again... ");
					inputType = m_inOut.readInput("");
				}
			}
	
			if (rangeType == 1)
			{
				type=Normal;
				
				break;
			}
			else if (rangeType == 2)
			{
				type=Warning;
				
				break;
			}
			else if (rangeType == 3)
			{
				type=Critical;
				
				break;
			}
			else
			{
				m_inOut.criticalAlert("Invalid input.  Try again... ");
				validRangeFlag = false;
			}
		} while (!validRangeFlag);

		return type;
		
	}
	std::string DeviceRegistrationUnit::getMessage()
	{
		string message = m_inOut.readMessage("Enter the message for type :");
		return message;

	}


	void DeviceRegistrationUnit::registerDevice()
	{
		Device newDevice;
		newDevice.deviceId = m_inOut.readInput("Enter Device ID : ");
		
		if (m_deviceRepository.checkDeviceExist(newDevice.deviceId))
		{
			m_inOut.criticalAlert("Device Id already Exist");
			return;
		}


		newDevice.validInputRange = getValidLimitsRange();

		newDevice.limits = getLimits(newDevice.validInputRange);

		if (m_deviceRepository.registerNew(newDevice))
		{

			m_inOut.warningAlert("Device successfully registered");
		}
		else
		{
			m_inOut.criticalAlert("Device registration failed");
		}
		
		
	}

	void DeviceRegistrationUnit::updateRegisteredDevices()
	{
		
		Device updateDevice;

		updateDevice.deviceId = m_inOut.readInput("Enter Device ID : ");
		if (!m_deviceRepository.checkDeviceExist(updateDevice.deviceId))
		{
			m_inOut.criticalAlert("Device Id does not Exist");
			return;
		}

		updateDevice.validInputRange = getValidLimitsRange();

		updateDevice.limits = getLimits(updateDevice.validInputRange);

		if (m_deviceRepository.update(updateDevice))
		{
			m_inOut.warningAlert("Device successfully updated");
		}
		else
		{
			m_inOut.criticalAlert("Device updation failed");
		}

	}

	void DeviceRegistrationUnit::readAllRegisteredDevices()
	{
		vector<Device> devicesList;

		devicesList.clear();
		devicesList = m_deviceRepository.readAll();
		if (devicesList.size() == 0)
		{
			m_inOut.display("No Device found");
			return;
		}
		for (auto i = devicesList.begin(); i != devicesList.end(); i++)
			m_inOut.display(i->toString());
		/*if (devicesList.size() == 0)
		{
			m_inOut.criticalAlert("No Device found");
		}
		else
		{
			for(Device device:devicesList)
			{
				m_inOut.warningAlert("\n\nDevice Id : "+ device.deviceId);
				m_inOut.warningAlert("Device Vaild input range : "+to_string(device.validInputRange.min)+" to "+to_string(device.validInputRange.max));
				for (int i = 0; i < device.limits.size(); i++)
				{
					m_inOut.warningAlert("Type : "+ getEnumTypeName(device.limits[i].type)+ " Range :"+to_string(device.limits[i].range.min)+" to "+to_string(device.limits[i].range.max));
					m_inOut.warningAlert("Message : "+ device.limits[i].message);
				}

				
			}
		}*/

	}

	void DeviceRegistrationUnit::readRegisteredDevice()
	{
		string deviceId = m_inOut.readInput("Enter Device ID : ");
		
		Device device = (m_deviceRepository.read(deviceId));
		if (device.deviceId == "")
		{
			m_inOut.display("Device ID not found. ");

		}
		else
			m_inOut.display(device.toString());

		/*if (device.deviceId == "")
		{
			m_inOut.criticalAlert("Device Id not found");
		}
		else
		{
			string enumName;
			m_inOut.warningAlert("Device Id : " + device.deviceId);
			m_inOut.warningAlert("Device Vaild input range : " + to_string(device.validInputRange.min) + " to " + to_string(device.validInputRange.max));
			for (int i = 0; i < device.limits.size(); i++)
			{
				
				

				m_inOut.warningAlert("Type : " + getEnumTypeName(device.limits[i].type) + " Range :" + to_string(device.limits[i].range.min) + " to " + to_string(device.limits[i].range.max));
				m_inOut.warningAlert("Message : " + device.limits[i].message);
			}
		}
*/
	}
	void DeviceRegistrationUnit::deleteRegisteredDevice()
	{
		string deviceId = m_inOut.readInput("Enter Device ID : ");
		
		if (m_deviceRepository.remove(deviceId))
		{
			m_inOut.warningAlert("Device Id " + deviceId + " successfully deleted");
		}
		else
		{
			m_inOut.criticalAlert("Deletion is failed");
		}
	}


	string DeviceRegistrationUnit::getEnumTypeName(int value)
	{
		if (value == 0)
			return "Normal";
		else if (value == 1)
			return "Warning";
		else
			return "Critical";

	}
}

	

