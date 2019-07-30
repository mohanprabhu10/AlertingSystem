#pragma once
#include <string>
#include <vector>

namespace RulesBasedAlertingSystem
{
	class IInputOutputUnit
	{
	public:
		virtual ~IInputOutputUnit() = default;
		virtual std::string readInput(std::string menu) = 0;
		virtual std::string readMessage(std::string menu) = 0;
		virtual std::string readVitals() = 0;
		virtual void pause() = 0;
		virtual void display(std::string output) = 0;
		virtual void criticalAlert(std::string input) = 0;
		virtual void warningAlert(std::string input) = 0;
		virtual void clearScreen() = 0;
	};
}
