#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "assemble.h"

int carInfo[CARINFO_ARRAY_SIZE];

int main()
{
    // 초기 단계: 차 종류 선택
    int currentStep = SelectCarType;

    while (1)
    {
        printStep(currentStep);

        int answer = getInputFromUser();
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

        if (checkUserInputIsValid(currentStep, answer) == false)
        {
            // 에러 메시지는 checkUserInputIsValid()에서 이미 출력하였으므로, 딜레이 후 continue 실행
            delay(DELAY_TIME_MS);
            continue;
        }

        int isFirstStep = (currentStep == CurrentStep::SelectCarType);
        if (isFirstStep == false && answer == INPUT_MOVE_TO_PREVIOUS_STEP)
        {
            if (currentStep == SelectRunTest)
            {
                // 실행-테스트 메뉴: 처음으로 돌아가기
                currentStep = SelectCarType;
                continue;
            }

            // 이외: 이전으로 돌아가기
            if (currentStep > 0)
            {
                currentStep -= 1;
            }
            continue;
        }

        switch (currentStep)
        {
            case SelectCarType:
                selectCarType(answer);
                delay(DELAY_TIME_MS);
                currentStep = SelectEngine;
                break;
            case SelectEngine:
                selectEngine(answer);
                delay(DELAY_TIME_MS);
                currentStep = SelectBrakeSystem;
                break;
            case SelectBrakeSystem:
                selectBrakeSystem(answer);
                delay(DELAY_TIME_MS);
                currentStep = SelectSteeringSystem;
                break;
            case SelectSteeringSystem:
                selectSteeringSystem(answer);
                delay(DELAY_TIME_MS);
                currentStep = SelectRunTest;
                break;
            case SelectRunTest:
                selectRunTest(answer);
                break;
        }
    }
}

void printStep(int step)
{
    switch (step)
    {
        case SelectCarType:
            printStepCar();
            break;
        case SelectEngine:
            printStepEngine();
            break;
        case SelectBrakeSystem:
            printStepBrakeSystem();
            break;
        case SelectSteeringSystem:
            printStepSteeringSystem();
            break;
        case SelectRunTest:
            printStepRunTest();
            break;
    }
    printf("===============================\n");
}

void clearScreen()
{
    printf(CLEAR_SCREEN);
}

void printStepCar()
{
    clearScreen();
    printf("        ______________\n");
    printf("       /|            | \n");
    printf("  ____/_|_____________|____\n");
    printf(" |                      O  |\n");
    printf(" '-(@)----------------(@)--'\n");
    printf("===============================\n");
    printf("어떤 차량 타입을 선택할까요?\n");
    printf("1. Sedan\n");
    printf("2. SUV\n");
    printf("3. Truck\n");
}

void printStepEngine()
{
    clearScreen();
    printf("어떤 엔진을 탑재할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. GM\n");
    printf("2. TOYOTA\n");
    printf("3. WIA\n");
    printf("4. 고장난 엔진\n");
}

void printStepBrakeSystem()
{
    clearScreen();
    printf("어떤 제동장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. MANDO\n");
    printf("2. CONTINENTAL\n");
    printf("3. BOSCH\n");
}

void printStepSteeringSystem()
{
    clearScreen();
    printf("어떤 조향장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. BOSCH\n");
    printf("2. MOBIS\n");
}

void printStepRunTest()
{
    clearScreen();
    printf("멋진 차량이 완성되었습니다.\n");
    printf("어떤 동작을 할까요?\n");
    printf("0. 처음 화면으로 돌아가기\n");
    printf("1. RUN\n");
    printf("2. Test\n");
}

int getInputFromUser()
{
    char buf[BUF_SIZE];

    printf("INPUT > ");
    fgets(buf, sizeof(buf), stdin);

    removeCRLFFromBuffer(buf);

    if (checkUserInputIsExit(buf))
    {
        return INPUT_EXIT; // 종료를 의미
    }

    int isInputNumber = false;
    int input = parseInputAsNumber(&isInputNumber, buf);
    if (isInputNumber)
    {
        return input;
    }

    // 숫자가 아닌 잘못된 입력을 의미 (음수는 사용하지 않으므로 return 값으로 음수 사용)
    return INPUT_NOT_NUMBER;
}

void removeCRLFFromBuffer(char* buf)
{
    char* context = nullptr;
    (void)strtok_s(buf, "\r", &context);
    (void)strtok_s(buf, "\n", &context);
}

int checkUserInputIsExit(char* buf)
{
    // 만약 strcmp 값이 0이면 buf는 exit이라는 의미이므로, true를 리턴한다.
    return (strcmp(buf, "exit") == 0);
}

int parseInputAsNumber(int* outIsNumber, char* buf)
{
    char* checkNumber;
    int answer = strtol(buf, &checkNumber, 10); // 문자열을 10진수로 변환

    // 입력받은 문자가 숫자라면 checkNumber는 null이다. 
    if (*checkNumber == '\0')
    {
        *outIsNumber = 1;
        return answer;
    }

    // 입력받은 문자가 숫자가 아니면, outIsNumber를 0 (false)로 설정한 후 0을 반환한다.
    *outIsNumber = 0;
    return 0;
}


int checkUserInputIsValid(int currentStep, int answer)
{
    // 입력 범위를 확인하고 valid하지 않은 경우 false를 변경한다.
    switch (currentStep)
    {
    case SelectCarType:
        if (isAnswerWithinRange(answer, CARTYPE_INPUT_MIN, CARTYPE_INPUT_MAX) == false)
        {
            printf("ERROR :: 차량 타입은 %d ~ %d 범위만 선택 가능\n", CARTYPE_RANGE_MIN, CARTYPE_RANGE_MAX);
            return false;
        }
        break;
    case SelectEngine:
        if (isAnswerWithinRange(answer, ENGINE_INPUT_MIN, ENGINE_INPUT_MAX) == false)
        {
            printf("ERROR :: 엔진은 %d ~ %d 범위만 선택 가능\n", ENGINE_RANGE_MIN, ENGINE_RANGE_MAX);
            return false;
        }
        break;
    case SelectBrakeSystem:
        if (isAnswerWithinRange(answer, BRAKESYSTEM_INPUT_MIN, BRAKESYSTEM_INPUT_MAX) == false)
        {
            printf("ERROR :: 제동장치는 %d ~ %d 범위만 선택 가능\n", BRAKESYSTEM_RANGE_MIN, BRAKESYSTEM_RANGE_MAX);
            return false;
        }
        break;
    case SelectSteeringSystem:
        if (isAnswerWithinRange(answer, STEERINGSYSTEM_INPUT_MIN, STEERINGSYSTEM_INPUT_MAX) == false)
        {
            printf("ERROR :: 조향장치는 %d ~ %d 범위만 선택 가능\n", STEERINGSYSTEM_RANGE_MIN, STEERINGSYSTEM_RANGE_MAX);
            return false;
        }
        break;
    case SelectRunTest:
        if (isAnswerWithinRange(answer, RUNTEST_INPUT_MIN, RUNTEST_INPUT_MAX) == false)
        {
            printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
            return false;
        }
        break;
    }

    return true;
}

int isAnswerWithinRange(int answer, int rangeMin, int rangeMax)
{
    if (rangeMin > rangeMax)
    {
        return false;
    }

    return (rangeMin <= answer && answer <= rangeMax);
}

void selectCarType(int answer)
{
    const char* CAR_TYPE_MESSAGE_PART1 = "차량 타입으로 ";
    const char* CAR_TYPE_MESSAGE_PART2 = "을 선택하셨습니다.";

    const char* CAR_TYPE_SEDAN = "Sedan";
    const char* CAR_TYPE_SUV = "SUV";
    const char* CAR_TYPE_TRUCK = "Truck";

    if (answer < CARTYPE_RANGE_MIN || answer > CARTYPE_RANGE_MAX)
    {
        return;
    }

    carInfo[SelectCarType] = answer;
    printf("%s", CAR_TYPE_MESSAGE_PART1);
    switch (answer)
    {
        case CarType::SEDAN: // 1
            printf("%s", CAR_TYPE_SEDAN);
            break;
        case CarType::SUV: // 2
            printf("%s", CAR_TYPE_SUV);
            break;
        case CarType::TRUCK: // 3
            printf("%s", CAR_TYPE_TRUCK);
            break;
    }
    printf("%s\n", CAR_TYPE_MESSAGE_PART2);
}

void selectEngine(int answer)
{
    const char* ENGINE_MESSAGE = " 엔진을 선택하셨습니다.";

    const char* ENGINE_MAKER_GM = "GM";
    const char* ENGINE_MAKER_TOYOTA = "TOYOTA";
    const char* ENGINE_MAKER_WIA = "WIA";

    if (answer < ENGINE_RANGE_MIN || answer > ENGINE_RANGE_MAX)
    {
        return;
    }

    carInfo[SelectEngine] = answer;
    switch (answer)
    {
        case Engine::GM: // 1
            printf("%s", ENGINE_MAKER_GM);
            break;
        case Engine::TOYOTA: // 2
            printf("%s", ENGINE_MAKER_TOYOTA);
            break;
        case Engine::WIA: // 3
            printf("%s", ENGINE_MAKER_WIA);
            break;
    }

    switch (answer)
    {
        case Engine::GM: // 1
        case Engine::TOYOTA: // 2
        case Engine::WIA: // 3
            printf("%s\n", ENGINE_MESSAGE);
            break;
    }
}

void selectBrakeSystem(int answer)
{
    const char* BRAKESYSTEM_MESSAGE = " 제동장치를 선택하셨습니다.";

    const char* BRAKESYSTEM_MAKER_MANDO = "MANDO";
    const char* BRAKESYSTEM_MAKER_CONTINENTAL = "CONTINENTAL";
    const char* BRAKESYSTEM_MAKER_BOSCH = "BOSCH";

    if (answer < BRAKESYSTEM_RANGE_MIN || answer > BRAKESYSTEM_RANGE_MAX)
    {
        return;
    }

    carInfo[SelectBrakeSystem] = answer;
    switch (answer)
    {
        case BrakeSystem::MANDO: // 1
            printf("%s", BRAKESYSTEM_MAKER_MANDO);
            break;
        case BrakeSystem::CONTINENTAL: // 2
            printf("%s", BRAKESYSTEM_MAKER_CONTINENTAL);
            break;
        case BrakeSystem::BOSCH_B: // 3
            printf("%s", BRAKESYSTEM_MAKER_BOSCH);
            break;
    }
    printf("%s\n", BRAKESYSTEM_MESSAGE);
}

void selectSteeringSystem(int answer)
{
    const char* STEERINGSYSTEM_MESSAGE = " 조향장치를 선택하셨습니다.";

    const char* STEERINGSYSTEM_MAKER_BOSCH = "BOSCH";
    const char* STEERINGSYSTEM_MAKER_MOBIS = "MOBIS";

    if (answer < STEERINGSYSTEM_RANGE_MIN || answer > STEERINGSYSTEM_RANGE_MAX)
    {
        return;
    }

    carInfo[SelectSteeringSystem] = answer;
    switch (answer)
    {
        case SteeringSystem::BOSCH_S: // 1
            printf("%s", STEERINGSYSTEM_MAKER_BOSCH);
            break;
        case SteeringSystem::MOBIS: // 2
            printf("%s", STEERINGSYSTEM_MAKER_MOBIS);
            break;
    }
    printf("%s\n", STEERINGSYSTEM_MESSAGE);
}

void selectRunTest(int answer)
{
    switch (answer)
    {
        case RUNTEST_INPUT_RUN:
            runProducedCar();
            delay(DELAY_RUNTEST_2000MS);
            break;
        case RUNTEST_INPUT_TEST:
            printf("Test...\n");
            delay(DELAY_RUNTEST_1500MS);
            testProducedCar();
            delay(DELAY_RUNTEST_2000MS);
            break;
    }
}

int isValidCheck()
{
    switch (carInfo[SelectCarType]) {
    case SEDAN:
        if (carInfo[SelectBrakeSystem] == CONTINENTAL)
        {
            return false;
        }
        break;
    case SUV:
        if (carInfo[SelectEngine] == TOYOTA)
        {
            return false;
        }
        break;
    case TRUCK:
        if (carInfo[SelectEngine] == WIA)
        {
            return false;
        }
        if (carInfo[SelectBrakeSystem] == MANDO)
        {
            return false;
        }
        break;
    }

    if (carInfo[SelectBrakeSystem] == BOSCH_B && carInfo[SelectSteeringSystem] != BOSCH_S)
    {
        return false;
    }

    return true;
}

void runProducedCar()
{
    const char* CARTYPE_SEDAN = "Sedan";
    const char* CARTYPE_SUV = "SUV";
    const char* CARTYPE_TRUCK = "Truck";

    const char* MAKER_BOSCH = "Bosch";
    const char* MAKER_CONTINENTAL = "Continental";
    const char* MAKER_GM = "GM";
    const char* MAKER_MANDO = "Mando";
    const char* MAKER_MOBIS = "Mobis";
    const char* MAKER_TOYOTA = "TOYOTA";
    const char* MAKER_WIA = "WIA";

    if (isValidCheck() == false)
    {
        printf("자동차가 동작되지 않습니다\n");
        return;
    }
    else if (carInfo[SelectEngine] == Engine::MALFUNCTIONING)
    {
        printf("엔진이 고장나있습니다.\n");
        printf("자동차가 움직이지 않습니다.\n");
        return;
    }

    printf("Car Type : ");
    switch (carInfo[SelectCarType])
    {
        case CarType::SEDAN:
            printf("%s\n", CARTYPE_SEDAN);
            break;
        case CarType::SUV:
            printf("%s\n", CARTYPE_SUV);
            break;
        case CarType::TRUCK:
            printf("%s\n", CARTYPE_TRUCK);
            break;
    }

    printf("Engine : ");
    switch (carInfo[SelectEngine])
    {
        case Engine::GM:
            printf("%s\n", MAKER_GM);
            break;
        case Engine::TOYOTA:
            printf("%s\n", MAKER_TOYOTA);
            break;
        case Engine::WIA:
            printf("%s\n", MAKER_WIA);
            break;
    }

    printf("Brake System : ");
    switch (carInfo[SelectBrakeSystem])
    {
        case BrakeSystem::MANDO:
            printf("%s\n", MAKER_MANDO);
            break;
        case BrakeSystem::CONTINENTAL:
            printf("%s\n", MAKER_CONTINENTAL);
            break;
        case BrakeSystem::BOSCH_B:
            printf("%s\n", MAKER_BOSCH);
            break;
    }

    printf("SteeringSystem : ");
    switch (carInfo[SelectSteeringSystem])
    {
        case SteeringSystem::BOSCH_S:
            printf("%s\n", MAKER_BOSCH);
            break;
        case SteeringSystem::MOBIS:
            printf("%s\n", MAKER_MOBIS);
            break;
    }

    printf("자동차가 동작됩니다.\n");
}

void testProducedCar()
{
    const char* REASON_SEDAN_CANNOT_USE_CONTINENTAL_BRAKESYSTEM = "Sedan에는 Continental제동장치 사용 불가\0";
    const char* REASON_SUV_CANNOT_USE_TOYOTA_ENGINE = "SUV에는 TOYOTA엔진 사용 불가\0";
    const char* REASON_TRUCK_CANNOT_USE_WIA_ENGINE = "Truck에는 WIA엔진 사용 불가\0";
    const char* REASON_TRUCK_CANNOT_USE_MANDO_BRAKESYSTEM = "Truck에는 Mando제동장치 사용 불가\0";
   
    const char* ERROR_MESSAGE_ONLY_BOSCH_STEERINGSYSTEM_FOR_BOSCH_BRAKESYSTEM_PART1 = "Bosch 제동장치에는 ";
    const char* ERROR_MESSAGE_ONLY_BOSCH_STEERINGSYSTEM_FOR_BOSCH_BRAKESYSTEM_PART2 = "조향장치 사용 불가\0";
    const char* STEERINGSYSTEM_MAKER_MOBIS = "Mobis\0";

    char reason[BUF_SIZE] = { '\0' };

    int isPassed = true;

    switch (carInfo[SelectCarType])
    {
        case SEDAN:
            if (carInfo[SelectBrakeSystem] == CONTINENTAL)
            {
                isPassed = false;
                strncpy_s(reason, REASON_SEDAN_CANNOT_USE_CONTINENTAL_BRAKESYSTEM, BUF_SIZE);
            }
            break;
        case SUV:
            if (carInfo[SelectEngine] == TOYOTA)
            {
                isPassed = false;
                strncpy_s(reason, REASON_SUV_CANNOT_USE_TOYOTA_ENGINE, BUF_SIZE);
            }
            break;
        case TRUCK:
            if (carInfo[SelectEngine] == WIA)
            {
                isPassed = false;
                strncpy_s(reason, REASON_TRUCK_CANNOT_USE_WIA_ENGINE, BUF_SIZE);
            }
            else if (carInfo[SelectBrakeSystem] == MANDO)
            {
                isPassed = false;
                strncpy_s(reason, REASON_TRUCK_CANNOT_USE_MANDO_BRAKESYSTEM, BUF_SIZE);
            }
            break;
    }

    if (isPassed)
    {
        /* 원 코드에서는 차 분류에 따른 부품 조합 테스트를 통과한 경우만 Bosch 제동장치 - Bosch 조향장치 테스트를 확인한다.
         * 이에 리팩토링 시에도 차 분류에 따른 부품 조합 테스트를 통과한 후에만 해당 사항을 확인하도록 한다.
         */
        if (carInfo[SelectBrakeSystem] == BOSCH_B && carInfo[SelectSteeringSystem] != BOSCH_S)
        {
            isPassed = false;

            char steeringSystemMaker[BUF_SIZE] = { '\0' };
            switch (carInfo[SelectSteeringSystem])
            {
                case MOBIS:
                    strncpy_s(steeringSystemMaker, STEERINGSYSTEM_MAKER_MOBIS, BUF_SIZE);
                    break;
            }

            strncpy_s(reason, ERROR_MESSAGE_ONLY_BOSCH_STEERINGSYSTEM_FOR_BOSCH_BRAKESYSTEM_PART1, BUF_SIZE);
            strcat_s(reason, steeringSystemMaker);
            strcat_s(reason, ERROR_MESSAGE_ONLY_BOSCH_STEERINGSYSTEM_FOR_BOSCH_BRAKESYSTEM_PART2);
        }
    }

    printf("자동차 부품 조합 테스트 결과 : %s\n", (isPassed ? "PASS" : "FAIL"));
    if (isPassed == false)
    {
        printf("%s\n", reason);
    }
}

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
