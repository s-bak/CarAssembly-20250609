#include <map>
#include "MenuStepClasses.cpp"

class MenuLinkHandler {
private:
	MenuStep* previousStep = nullptr;
	MenuStep* nextStep = nullptr;
public:
	MenuLinkHandler(MenuStep* previousStep_, MenuStep* nextStep_)
	{
		setPrevStep(previousStep_);
		setNextStep(nextStep_);
	}

	void setPrevStep(const MenuStep* previousStep_)
	{
		previousStep = (MenuStep*)previousStep_;
	}
	MenuStep* getPrevStep()
	{
		return previousStep;
	}

	void setNextStep(const MenuStep* nextStep_)
	{
		nextStep = (MenuStep*)nextStep_;
	}
	MenuStep* getNextStep()
	{
		return nextStep;
	}
};

class MenuManager {
private:
	MenuStep* stepSelectCarType = (new SelectCarTypeMenuStepFactory())->createMenuStep();
	MenuStep* stepSelectEngine = (new SelectEngineMenuStepFactory())->createMenuStep();
	MenuStep* stepSelectBrakeSystem = (new SelectBrakeSystemMenuStepFactory())->createMenuStep();
	MenuStep* stepSelectSteeringSystem = (new SelectSteeringSystemMenuStepFactory())->createMenuStep();
	MenuStep* stepSelectRunTest = (new SelectRunTestMenuStepFactory())->createMenuStep();

	map<MenuStep*, MenuLinkHandler*> menuMap;
	MenuStep* currentStep;
public:
	MenuManager()
	{
		currentStep = stepSelectCarType;

		MenuLinkHandler* selectCarTypeLink = new MenuLinkHandler(stepSelectCarType, stepSelectEngine);
		MenuLinkHandler* selectEngineLink = new MenuLinkHandler(stepSelectCarType, stepSelectBrakeSystem);
		MenuLinkHandler* selectBrakeSystemLink = new MenuLinkHandler(stepSelectEngine, stepSelectSteeringSystem);
		MenuLinkHandler* selectSteeringSystemLink = new MenuLinkHandler(stepSelectBrakeSystem, stepSelectRunTest);
		MenuLinkHandler* selectRunTestLink = new MenuLinkHandler(stepSelectCarType, stepSelectRunTest);

		menuMap.insert({ stepSelectCarType, selectCarTypeLink });
		menuMap.insert({ stepSelectEngine, selectEngineLink });
		menuMap.insert({ stepSelectBrakeSystem, selectBrakeSystemLink });
		menuMap.insert({ stepSelectSteeringSystem, selectSteeringSystemLink });
		menuMap.insert({ stepSelectRunTest, selectRunTestLink });
	}
	void printCurrentMenu()
	{
		currentStep->printMenu();
	}

	int getInputFromUser()
	{
		cout << "INPUT > ";

		string input;
		cin >> input;

		if (input._Equal("exit"))
		{
			return INPUT_EXIT;
		}

		char* checkNumber;
		int answer = strtol(input.c_str(), &checkNumber, 10); // 문자열을 10진수로 변환
		
		// 입력받은 문자가 숫자가 아니라면 checkNumber는 null이 아닌 값이 담겨있다. 
		if (*checkNumber != '\0')
		{
			return INPUT_NOT_NUMBER;
		}
		
		// 현재 메뉴에 따라 입력을 검증한다.
		switch (answer)
		{
			case 0:
				currentStep = menuMap[currentStep]->getPrevStep();
				break;
			default:
				if (currentStep->validateInput(answer)) {
					currentStep->setInput(answer);
					currentStep->printValue();
					currentStep = menuMap[currentStep]->getNextStep();
				}
				break;
		}

		return answer;
	}

	int isValidCheck()
	{
		string carClass = stepSelectCarType->getEntryWithIndex(stepSelectCarType->getInput());
		string engineSystem = stepSelectEngine->getEntryWithIndex(stepSelectEngine->getInput());
		string brakeSystem = stepSelectBrakeSystem->getEntryWithIndex(stepSelectBrakeSystem->getInput());
		string steeringSystem = stepSelectBrakeSystem->getEntryWithIndex(stepSelectBrakeSystem->getInput());

		if (carClass == "Sedan")
		{
			if (brakeSystem == "CONTINENTAL") {
				return false;
			}
		}
		else if (carClass == "SUV") {
			if (engineSystem == "TOYOTA") {
				return false;
			}

		}
		else if (carClass == "Truck") {
			if (engineSystem == "WIA") {
				return false;
			}
			if (brakeSystem == "MANDO") {
				return false;
			}
		}

		if (brakeSystem == "BOSCH" && steeringSystem != "BOSCH")
		{
			return false;
		}

		return true;
	}
};