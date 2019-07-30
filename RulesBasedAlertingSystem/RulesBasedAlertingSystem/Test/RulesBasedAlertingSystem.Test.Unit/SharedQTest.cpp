#include "SharedQTest.h"
#include<string>
#include<thread>


void RulesBasedAlertingSystem::Test::Unit::SharedQTest::EnqueueTest(SharedQueue &sq)
{
	PatientVitals vitals;
	vitals.vitals.push_back({ "23", 10.9 });
	for (int i = 0; i < 10; i++)
	{
		vitals.patientId = std::to_string(i);
		sq.enqueue(vitals);
	}
	return;
}
