#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "CarManufactureManager.cpp"

void delay(int ms)
{
	volatile int sum = 0;
	for (int i = 0; i < 1000; i++)
	{
		for (int j = 0; j < 1000; j++)
		{
			for (int t = 0; t < ms; t++)
			{
				sum++;
			}
		}
	}
}

int main()
{
	CarManufactureManager menuManager = CarManufactureManager();
	while (1)
	{
		menuManager.printCurrentMenu();
		int answer = menuManager.getInputFromUser();
		if (answer == INPUT_EXIT)
		{
			printf("바이바이\n");
			break;
		}
		if (answer == INPUT_NOT_NUMBER) {
			printf("ERROR :: 숫자만 입력 가능\n");
			delay(DELAY_TIME_MS);
			continue;
		}
	}
}

//int isValidCheck()
//{
//    switch (carInfo[SelectCarType]) {
//    case SEDAN:
//        if (carInfo[SelectBrakeSystem] == CONTINENTAL)
//        {
//            return false;
//        }
//        break;
//    case SUV:
//        if (carInfo[SelectEngine] == TOYOTA)
//        {
//            return false;
//        }
//        break;
//    case TRUCK:
//        if (carInfo[SelectEngine] == WIA)
//        {
//            return false;
//        }
//        if (carInfo[SelectBrakeSystem] == MANDO)
//        {
//            return false;
//        }
//        break;
//    }
//
//    if (carInfo[SelectBrakeSystem] == BOSCH_B && carInfo[SelectSteeringSystem] != BOSCH_S)
//    {
//        return false;
//    }
//
//    return true;
//}
//
//void runProducedCar()
//{
//    const char* CARTYPE_SEDAN = "Sedan";
//    const char* CARTYPE_SUV = "SUV";
//    const char* CARTYPE_TRUCK = "Truck";
//
//    const char* MAKER_BOSCH = "Bosch";
//    const char* MAKER_CONTINENTAL = "Continental";
//    const char* MAKER_GM = "GM";
//    const char* MAKER_MANDO = "Mando";
//    const char* MAKER_MOBIS = "Mobis";
//    const char* MAKER_TOYOTA = "TOYOTA";
//    const char* MAKER_WIA = "WIA";
//
//    if (isValidCheck() == false)
//    {
//        printf("자동차가 동작되지 않습니다\n");
//        return;
//    }
//    else if (carInfo[SelectEngine] == Engine::MALFUNCTIONING)
//    {
//        printf("엔진이 고장나있습니다.\n");
//        printf("자동차가 움직이지 않습니다.\n");
//        return;
//    }
//
//    printf("Car Type : ");
//    switch (carInfo[SelectCarType])
//    {
//        case CarType::SEDAN:
//            printf("%s\n", CARTYPE_SEDAN);
//            break;
//        case CarType::SUV:
//            printf("%s\n", CARTYPE_SUV);
//            break;
//        case CarType::TRUCK:
//            printf("%s\n", CARTYPE_TRUCK);
//            break;
//    }
//
//    printf("Engine : ");
//    switch (carInfo[SelectEngine])
//    {
//        case Engine::GM:
//            printf("%s\n", MAKER_GM);
//            break;
//        case Engine::TOYOTA:
//            printf("%s\n", MAKER_TOYOTA);
//            break;
//        case Engine::WIA:
//            printf("%s\n", MAKER_WIA);
//            break;
//    }
//
//    printf("Brake System : ");
//    switch (carInfo[SelectBrakeSystem])
//    {
//        case BrakeSystem::MANDO:
//            printf("%s\n", MAKER_MANDO);
//            break;
//        case BrakeSystem::CONTINENTAL:
//            printf("%s\n", MAKER_CONTINENTAL);
//            break;
//        case BrakeSystem::BOSCH_B:
//            printf("%s\n", MAKER_BOSCH);
//            break;
//    }
//
//    printf("SteeringSystem : ");
//    switch (carInfo[SelectSteeringSystem])
//    {
//        case SteeringSystem::BOSCH_S:
//            printf("%s\n", MAKER_BOSCH);
//            break;
//        case SteeringSystem::MOBIS:
//            printf("%s\n", MAKER_MOBIS);
//            break;
//    }
//
//    printf("자동차가 동작됩니다.\n");
//}
//
//void testProducedCar()
//{
//    const char* REASON_SEDAN_CANNOT_USE_CONTINENTAL_BRAKESYSTEM = "Sedan에는 Continental제동장치 사용 불가\0";
//    const char* REASON_SUV_CANNOT_USE_TOYOTA_ENGINE = "SUV에는 TOYOTA엔진 사용 불가\0";
//    const char* REASON_TRUCK_CANNOT_USE_WIA_ENGINE = "Truck에는 WIA엔진 사용 불가\0";
//    const char* REASON_TRUCK_CANNOT_USE_MANDO_BRAKESYSTEM = "Truck에는 Mando제동장치 사용 불가\0";
//   
//    const char* ERROR_MESSAGE_ONLY_BOSCH_STEERINGSYSTEM_FOR_BOSCH_BRAKESYSTEM_PART1 = "Bosch 제동장치에는 ";
//    const char* ERROR_MESSAGE_ONLY_BOSCH_STEERINGSYSTEM_FOR_BOSCH_BRAKESYSTEM_PART2 = "조향장치 사용 불가\0";
//    const char* STEERINGSYSTEM_MAKER_MOBIS = "Mobis\0";
//
//    char reason[BUF_SIZE] = { '\0' };
//
//    int isPassed = true;
//
//    switch (carInfo[SelectCarType])
//    {
//        case SEDAN:
//            if (carInfo[SelectBrakeSystem] == CONTINENTAL)
//            {
//                isPassed = false;
//                strncpy_s(reason, REASON_SEDAN_CANNOT_USE_CONTINENTAL_BRAKESYSTEM, BUF_SIZE);
//            }
//            break;
//        case SUV:
//            if (carInfo[SelectEngine] == TOYOTA)
//            {
//                isPassed = false;
//                strncpy_s(reason, REASON_SUV_CANNOT_USE_TOYOTA_ENGINE, BUF_SIZE);
//            }
//            break;
//        case TRUCK:
//            if (carInfo[SelectEngine] == WIA)
//            {
//                isPassed = false;
//                strncpy_s(reason, REASON_TRUCK_CANNOT_USE_WIA_ENGINE, BUF_SIZE);
//            }
//            else if (carInfo[SelectBrakeSystem] == MANDO)
//            {
//                isPassed = false;
//                strncpy_s(reason, REASON_TRUCK_CANNOT_USE_MANDO_BRAKESYSTEM, BUF_SIZE);
//            }
//            break;
//    }
//
//    if (isPassed)
//    {
//        /* 원 코드에서는 차 분류에 따른 부품 조합 테스트를 통과한 경우만 Bosch 제동장치 - Bosch 조향장치 테스트를 확인한다.
//         * 이에 리팩토링 시에도 차 분류에 따른 부품 조합 테스트를 통과한 후에만 해당 사항을 확인하도록 한다.
//         */
//        if (carInfo[SelectBrakeSystem] == BOSCH_B && carInfo[SelectSteeringSystem] != BOSCH_S)
//        {
//            isPassed = false;
//
//            char steeringSystemMaker[BUF_SIZE] = { '\0' };
//            switch (carInfo[SelectSteeringSystem])
//            {
//                case MOBIS:
//                    strncpy_s(steeringSystemMaker, STEERINGSYSTEM_MAKER_MOBIS, BUF_SIZE);
//                    break;
//            }
//
//            strncpy_s(reason, ERROR_MESSAGE_ONLY_BOSCH_STEERINGSYSTEM_FOR_BOSCH_BRAKESYSTEM_PART1, BUF_SIZE);
//            strcat_s(reason, steeringSystemMaker);
//            strcat_s(reason, ERROR_MESSAGE_ONLY_BOSCH_STEERINGSYSTEM_FOR_BOSCH_BRAKESYSTEM_PART2);
//        }
//    }
//
//    printf("자동차 부품 조합 테스트 결과 : %s\n", (isPassed ? "PASS" : "FAIL"));
//    if (isPassed == false)
//    {
//        printf("%s\n", reason);
//    }
//}
//
//void delay(int ms)
//{
//    volatile int sum = 0;
//    for (int i = 0; i < 1000; i++)
//    {
//        for (int j = 0; j < 1000; j++)
//        {
//            for (int t = 0; t < ms; t++)
//            {
//                sum++;
//            }
//        }
//    }
//}
