#include "MockInputOutput.h"
#include "../../RulesBasedAlertingSystem/PatientVitals.h"

namespace RulesBasedAlertingSystem
{
	namespace Test
	{
		namespace Unit
		{
			std::string MockInputOutput::readInput(std::string menu)
			{
				return{};
			}

			std::string MockInputOutput::readMessage(std::string menu)
			{
				return{};
			}

			std::string MockInputOutput::readVitals()
			{
				std::string input = "{ \"patientId\" : \"11\" , \"100\" : 55.5, \"200\" : 63.5, \"300\" : 66.5}";
				return input;

			}

			void MockInputOutput::pause()
			{
				return;
			}

			void MockInputOutput::display(std::string output)
			{
				return;
			}

			void MockInputOutput::criticalAlert(std::string input)
			{
				critical.push_back(input);
				return;
			}

			void MockInputOutput::warningAlert(std::string input)
			{
				warning.push_back(input);
				return;
			}

			void MockInputOutput::clearScreen()
			{
				return;
			}
		}
	}

}
