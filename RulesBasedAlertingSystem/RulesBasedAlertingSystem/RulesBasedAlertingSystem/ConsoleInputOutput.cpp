#include "ConsoleInputOutput.h"
#include "iostream"
#include <windows.h>
#include <stdlib.h>

namespace RulesBasedAlertingSystem
{
	std::string ConsoleInputOutput::readInput(std::string menu)
	{
		std::cout << menu << std::endl;
		std::string input;
		std::cin >> input;
		return input;
	}

	std::string ConsoleInputOutput::readMessage(std::string menu)
	{
		std::cout << menu << std::endl;
		std::cin.ignore();
		std::string input;
		std::getline(std::cin, input);
		return input;
	}

	void ConsoleInputOutput::display(std::string output)
	{
		std::cout << output << std::endl;

	}

	std::string ConsoleInputOutput::readVitals()
	{
		std::string input;
		std::getline(std::cin, input);
		return input;
	}

	void ConsoleInputOutput::pause()
	{
		system("pause");
	}

	void ConsoleInputOutput::criticalAlert(std::string input)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << input << std::endl;
		SetConsoleTextAttribute(hConsole, 7);
	}

	void ConsoleInputOutput::warningAlert(std::string input)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);
		std::cout << input << std::endl;
		SetConsoleTextAttribute(hConsole, 7);
	}
	void ConsoleInputOutput::clearScreen()
	{
		system("CLS");
	}
}