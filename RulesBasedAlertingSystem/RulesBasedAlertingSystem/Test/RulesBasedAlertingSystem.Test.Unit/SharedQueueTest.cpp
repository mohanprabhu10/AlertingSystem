#include "gtest\gtest.h"
#include "../../RulesBasedAlertingSystem/SharedQueue.h"
#include<thread>
#include<string>
#include "SharedQTest.h"
namespace RulesBasedAlertingSystem
{
	namespace Test
	{
		namespace Unit
		{
			class SharedQueueTest : public ::testing::Test
			{
			
			};

			TEST_F(SharedQueueTest, BasicPushPopTest)
			{
				PatientVitals vitals;
				vitals.patientId = "123";
				vitals.vitals.push_back({ "23",10.9 });
				SharedQueue sq;
				EXPECT_EQ(sq.isEmpty(), true);
				sq.enqueue(vitals);
				EXPECT_EQ(sq.isEmpty(), false);
				PatientVitals &testvitals = sq.dequeue();
				EXPECT_EQ(testvitals.patientId, vitals.patientId);
				EXPECT_EQ(sq.isEmpty(), true);

			}

			TEST_F(SharedQueueTest, ThreadingTest)
			{
				PatientVitals vitals;
				vitals.patientId = "123";
				vitals.vitals.push_back({ "23", 10.9 });
				SharedQueue sq;
				std::thread EnqueueThread(&SharedQueue::enqueue, &sq, vitals);
				PatientVitals TestVitals = sq.dequeue();
				EnqueueThread.join();
				EXPECT_EQ(sq.isEmpty(), true);
			}
		
			TEST_F(SharedQueueTest, MultiplePushPopThreading)
			{
				SharedQTest SqTest;
				SharedQueue sq;
				PatientVitals vitals;
				vitals.patientId = "111";
				vitals.vitals.push_back({ "23", 10.9 });
				//std::thread EnqueueThread(&SharedQueue::enqueue, &sq, vitals);
				PatientVitals TestVitalsComapre[10];
				for (int i = 0; i < 10; i++)
				{
					vitals.patientId = std::to_string(i);
					std::thread EnqueueThread(&SharedQueue::enqueue, &sq, vitals);
					TestVitalsComapre[i] = vitals;
					EnqueueThread.join();
				}
				ASSERT_EQ(sq.isEmpty(), false);
				PatientVitals TestVitals[10];
				for (int i = 0; i < 10; i++)
				{
					TestVitals[i] = sq.dequeue();
					EXPECT_EQ(TestVitals[i].patientId, TestVitalsComapre[i].patientId);
				}
				
				//EnqueueThread.join();
				ASSERT_EQ(sq.isEmpty(), true);
			}


		}
	}
}