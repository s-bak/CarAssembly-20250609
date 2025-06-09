#pragma once

#define CLEAR_SCREEN "\033[H\033[2J"

#define BUF_SIZE 100

#define DELAY_TIME_MS 800
#define DELAY_RUNTEST_1500MS 1500
#define DELAY_RUNTEST_2000MS 2000

#define INPUT_MOVE_TO_PREVIOUS_STEP 0
#define INPUT_EXIT -1
#define INPUT_NOT_NUMBER -2

#define RUNTEST_INPUT_RUN 1
#define RUNTEST_INPUT_TEST 2

#define CARTYPE_INPUT_MIN 1
#define CARTYPE_INPUT_MAX 3
#define CARTYPE_RANGE_MIN CARTYPE_INPUT_MIN
#define CARTYPE_RANGE_MAX CARTYPE_INPUT_MAX
#define ENGINE_INPUT_MIN 0
#define ENGINE_INPUT_MAX 4
#define ENGINE_RANGE_MIN ENGINE_INPUT_MIN + 1
#define ENGINE_RANGE_MAX ENGINE_INPUT_MAX
#define BRAKESYSTEM_INPUT_MIN 0
#define BRAKESYSTEM_INPUT_MAX 3
#define BRAKESYSTEM_RANGE_MIN BRAKESYSTEM_INPUT_MIN + 1
#define BRAKESYSTEM_RANGE_MAX BRAKESYSTEM_INPUT_MAX
#define STEERINGSYSTEM_INPUT_MIN 0
#define STEERINGSYSTEM_INPUT_MAX 2
#define STEERINGSYSTEM_RANGE_MIN BRAKESYSTEM_INPUT_MIN + 1
#define STEERINGSYSTEM_RANGE_MAX BRAKESYSTEM_INPUT_MAX
#define RUNTEST_INPUT_MIN 0
#define RUNTEST_INPUT_MAX 2

#define CARINFO_ARRAY_SIZE 5

enum CurrentStep
{
    SelectCarType,
    SelectEngine,
    SelectBrakeSystem,
    SelectSteeringSystem,
    SelectRunTest,
};

enum CarType
{
    SEDAN = 1,
    SUV,
    TRUCK
};

enum Engine
{
    GM = 1,
    TOYOTA,
    WIA,
    MALFUNCTIONING, // 고장난 엔진
};

enum BrakeSystem
{
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B
};

enum SteeringSystem
{
    BOSCH_S = 1,
    MOBIS
};

void printStep(int step);
void clearScreen();
void printStepCar();
void printStepEngine();
void printStepBrakeSystem();
void printStepSteeringSystem();
void printStepRunTest();

int getInputFromUser();
void removeCRLFFromBuffer(char* buf);
int checkUserInputIsExit(char* buf);
int parseInputAsNumber(int* outIsNumber, char* buf);
int checkUserInputIsValid(int currentStep, int answer);
int isAnswerWithinRange(int answer, int rangeMin, int rangeMax);

void selectCarType(int answer);
void selectEngine(int answer);
void selectBrakeSystem(int answer);
void selectSteeringSystem(int answer);
void selectRunTest(int answer);

int isValidCheck();
void runProducedCar();
void testProducedCar();

void delay(int ms);
