//#include "gtest\gtest.h"
//#include "../../RulesBasedAlertingSystem/ReceiverUnit.h"
//#include "MockInputOutput.h"
//#include "MockPatientRepo.h"
//
//namespace RulesBasedAlertingSystem
//{
//	namespace Test
//	{
//		namespace Unit
//		{
//			class ReceiverUnitTest : public ::testing::Test
//			{
//				
//			};
//
//			TEST_F(ReceiverUnitTest, ValidInputTest)
//			{
//				SharedQueue queue;
//				for (int i = 1; i < 4; i++)
//				{
//					PatientVitals vit;
//					vit.patientId = std::to_string(i) + std::to_string(i);
//					for(int j = 0; j <3; j++)
//					{
//						vit.vitals.push_back({ std::to_string((j * 100)), (j + 1)*27.5 });
//					}
//					
//				}
//
//				std::map<std::string, Patient> map;
//				MockPatientRepo repo;
//				auto patients = repo.readAll();
//				for (auto i = patients.begin(); i != patients.end(); i++)
//					map.insert({i->patientId, *i});
//				MockInputOutput inOut;
//				ReceiverUnit receiver(queue, map, inOut);
//
//				receiver.inputProcess();
//				
//			}
//		}
//	}
//}
