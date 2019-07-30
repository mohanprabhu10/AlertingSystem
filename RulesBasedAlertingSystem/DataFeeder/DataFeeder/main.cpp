#include "iostream"
#include "chrono"
#include "thread"
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
	std::cout << std::to_string(3) << std::endl;
	std::string path = "PatientMonitorData.txt";
	std::this_thread::sleep_for(std::chrono::seconds(5));
	std::string line;
	//std::cout << "3" << std::endl;
	std::ifstream infile;
	infile.open(path);
	if (infile.is_open())
	{
		while (std::getline(infile, line))
		{
			std::this_thread::sleep_for(std::chrono::seconds(2));
			std::cout << line <<  std::endl;
		}
		infile.close();
	}

	//int i = 2200;
	//while (1) {
	//	std::cout << "{ \"patientId\": \"TRJIW432\", \"SPO2\": 96, \"pulse rate\": 75, \"temperature\": 98.6 }" << std::endl;;
	//	i++;
	//	std::this_thread::sleep_for(std::chrono::seconds(2));
	//}
	/*std::cout << 10;*/
	return 0;
}
