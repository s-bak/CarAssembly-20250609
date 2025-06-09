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

class CarManufactureManager {
private:
	MenuStep* stepSelectCarType = (new SelectCarTypeMenuStepFactory())->createMenuStep();
	MenuStep* stepSelectEngine = (new SelectEngineMenuStepFactory())->createMenuStep();
	MenuStep* stepSelectBrakeSystem = (new SelectBrakeSystemMenuStepFactory())->createMenuStep();
	MenuStep* stepSelectSteeringSystem = (new SelectSteeringSystemMenuStepFactory())->createMenuStep();
	MenuStep* stepSelectRunTest = (new SelectRunTestMenuStepFactory())->createMenuStep();

	map<MenuStep*, MenuLinkHandler*> menuMap;
	MenuStep* currentStep;

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
public:
	CarManufactureManager()
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
		int answer = strtol(input.c_str(), &checkNumber, 10); // ���ڿ��� 10������ ��ȯ
		
		// �Է¹��� ���ڰ� ���ڰ� �ƴ϶�� checkNumber�� null�� �ƴ� ���� ����ִ�. 
		if (*checkNumber != '\0')
		{
			return INPUT_NOT_NUMBER;
		}
		
		// ���� �޴��� ���� �Է��� �����Ѵ�.
		switch (answer)
		{
			case 0:
				currentStep = menuMap[currentStep]->getPrevStep();
				break;
			default:
				if (currentStep->validateInput(answer)) {
					if (currentStep == stepSelectRunTest) {
						if (answer == 1) {
							runProducedCar();
						}
						else if (answer == 2) {
							testProducedCar();
						}
					}
					else {
						currentStep->setInput(answer);
						currentStep->printValue();
					}

					currentStep = menuMap[currentStep]->getNextStep();
				}
				break;
		}

		return answer;
	}

	void runProducedCar()
	{
		string carClass = stepSelectCarType->getEntryWithIndex(stepSelectCarType->getInput());
		string engineSystem = stepSelectEngine->getEntryWithIndex(stepSelectEngine->getInput());
		string brakeSystem = stepSelectBrakeSystem->getEntryWithIndex(stepSelectBrakeSystem->getInput());
		string steeringSystem = stepSelectBrakeSystem->getEntryWithIndex(stepSelectBrakeSystem->getInput());

		if (isValidCheck() == false) {
			cout << "�ڵ����� ���۵��� �ʽ��ϴ�" << endl;
			return;
		}

		if (engineSystem == "���峭 ����") {
			cout << "������ ���峪�ֽ��ϴ�." << endl;
			cout << "�ڵ����� �������� �ʽ��ϴ�." << endl;
			return;
		}

		cout << "Car Type : " << carClass << endl;
		cout << "Engine : " << engineSystem << endl;
		cout << "Brake System : " << brakeSystem << endl;
		cout << "SteeringSystem : " << steeringSystem << endl;
		cout << "�ڵ����� �����մϴ�." << endl;
	}

	void testProducedCar() {
		string carClass = stepSelectCarType->getEntryWithIndex(stepSelectCarType->getInput());
		string engineSystem = stepSelectEngine->getEntryWithIndex(stepSelectEngine->getInput());
		string brakeSystem = stepSelectBrakeSystem->getEntryWithIndex(stepSelectBrakeSystem->getInput());
		string steeringSystem = stepSelectBrakeSystem->getEntryWithIndex(stepSelectBrakeSystem->getInput());

		string errorString = "";
		string result = "PASS";

		if (carClass == "Sedan")
		{
			if (brakeSystem == "CONTINENTAL") {
				errorString = "Sedan���� Continental������ġ ��� �Ұ�";
				result = "FAIL";
			}
		}
		else if (carClass == "SUV") {
			if (engineSystem == "TOYOTA") {
				errorString =  "SUV���� TOYOTA���� ��� �Ұ�";
				result = "FAIL";
			}

		}
		else if (carClass == "Truck") {
			if (engineSystem == "WIA") {
				errorString = "Truck���� WIA���� ��� �Ұ�";
				result = "FAIL";
			}
			else if (brakeSystem == "MANDO") {
				errorString = "Truck���� Mando������ġ ��� �Ұ�";
				result = "FAIL";
			}
		}

		if (brakeSystem == "BOSCH" && steeringSystem != "BOSCH")
		{
			errorString = "Bosch ������ġ���� ";
			if (steeringSystem == "MOBIS") {
				errorString += steeringSystem;
			}
			errorString += "������ġ ��� �Ұ�";
			result = "FAIL";
		}

		cout << "�ڵ��� ��ǰ ���� �׽�Ʈ ��� : " << result << endl;
		if (errorString != "") {
			cout << errorString << endl;
		}
	}
};