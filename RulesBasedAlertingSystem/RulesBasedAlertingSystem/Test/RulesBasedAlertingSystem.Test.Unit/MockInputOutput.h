#pragma once
#include "..\..\RulesBasedAlertingSystem\IInputOutputUnit.h"

namespace RulesBasedAlertingSystem
{
	namespace Test
	{
		namespace Unit
		{
			class MockInputOutput : public IInputOutputUnit
			{
			public:
				std::string readInput(std::string menu) override;
				std::string readMessage(std::string menu) override;
				std::string readVitals() override;
				void pause() override;
				void display(std::string output) override;
				void criticalAlert(std::string input) override;
				void warningAlert(std::string input) override;
				void clearScreen() override;

				std::vector < std::string > critical;
				std::vector <std::string> warning;
			};
		}
	}

}