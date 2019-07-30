#pragma once
#include <string>
#include <vector>

namespace RulesBasedAlertingSystem
{
	struct Range
	{
		double min;
		double max;
		std::string toString()
		{
			return std::string("Min Value : " + std::to_string(min) + "\nMax value : " + std::to_string(max));
		}
	};
	enum Type
	{
		Normal,
		Warning,
		Critical
	};

	struct Limits
	{
		Range range;
		Type type;
		std::string message;
		std::string toString()
		{
			std::string typeString;
			switch (type)
			{
			case Normal:
				typeString = "Normal";
				break;
			case Warning:
				typeString = "Warning";
				break;
			case Critical:
				typeString = "Critical";
				break;
			default:
				typeString = "Invalid Type";
				break;
			}
			return std::string("Range : \n" + range.toString() + "\nType : " + typeString + "\nMessage : " + message);
		}
	};
	struct Device
	{
		std::string deviceId;
		Range validInputRange;
		std::vector<Limits> limits;

		std::string toString()
		{
			std::string output("Device ID : " + deviceId + "\nValid Input Range : \n" + validInputRange.toString()+"\nLimits : \n");
			for(auto i = limits.begin();i!=limits.end();i++)
			{
				output.append(i->toString() + "\n");
			}
			return output;
		}
	};
}
