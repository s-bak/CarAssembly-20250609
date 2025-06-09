#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "assemble.h"

using namespace std;

class MenuStep {
private:
	const string clearScreen = "\033[H\033[2J";

	int inputMin = 0;
	int input = 0;
	
	bool printBackMenu = false;
	string backMenuString = "";
	
protected:
	vector<string> entriesList;
	string nickname = "";
	string stringToPrintBeforeMenu = "";
public:
	int getInputMin()
	{
		return inputMin;
	}
	int getInputMax()
	{
		return entriesList.size();
	}
	bool isInputValid(int input)
	{
		int inputMax = getInputMax();
		if (inputMin > inputMax) {
			return false;
		}

		return (inputMin <= input && input <= inputMax);
	}
	bool validateInput(int input)
	{
		bool isValid = isInputValid(input);
		if (isValid == false)
		{
			cout << "ERROR :: " << nickname << " " << getRangeMin() << " ~ " << getRangeMax() << " 범위만 선택 가능" << endl;
		}

		return isValid;
	}

	int getInput() {
		return input;
	}
	void setInput(int input_) {
		input = input_;
	}
	string getEntryWithIndex(int index) {
		return entriesList.at(index - 1);
	}

	int getRangeMin()
	{
		// Range의 경우 0 (뒤로/맨처음으로 가기)를 제외한다.
		return 1;
	}
	int getRangeMax()
	{
		return entriesList.size();
	}

	void disableBackMenu()
	{
		printBackMenu = false;

		inputMin = 1;
	}

	void enableBackMenu(string backMenuString_ = "뒤로가기")
	{
		printBackMenu = true;
		backMenuString = backMenuString_;

		inputMin = 0;
	}

	void addEntry(string entry) {
		entriesList.push_back(entry);
	}

	void cleanEntriesList() {
		entriesList.clear();
	}

	void printMenu() {
		cout << clearScreen;

		if (stringToPrintBeforeMenu.length() > 0) {
			cout << stringToPrintBeforeMenu << endl;
		}

		if (printBackMenu) {
			cout << "0. " << backMenuString << endl;
		}

		int entryIndex = 1;
		for (string entry : entriesList)
		{
			cout << entryIndex << ". " << entry << endl;
			entryIndex += 1;
		}
	}
	virtual void setNickname() = 0;
	virtual void setStringBeforePrintingMenu() = 0;
	virtual void setBackMenu() = 0;
	virtual void addEntries() = 0;
	virtual void printValue() = 0;

	virtual ~MenuStep() {} // Virtual destructor for polymorphism
};

class MenuStepFactory {
public:
	virtual MenuStep* createMenuStep() = 0;
	virtual ~MenuStepFactory() {} // Virtual destructor for polymorphism
};

class SelectCarTypeMenuStep: public MenuStep {
public:
	void setNickname() override {
		nickname = "차량 타입은";
	}
	void setStringBeforePrintingMenu() override {
		stringToPrintBeforeMenu.append("        ______________\n");
		stringToPrintBeforeMenu.append("       /|            | \n");
		stringToPrintBeforeMenu.append("  ____/_|_____________|____\n");
		stringToPrintBeforeMenu.append(" |                      O  |\n");
		stringToPrintBeforeMenu.append(" '-(@)----------------(@)--'\n");
		stringToPrintBeforeMenu.append("===============================\n");
		stringToPrintBeforeMenu.append("어떤 차량 타입을 선택할까요?");
	}

	void setBackMenu() override {
		// No backmenu for Select Car Type, so empty body
	}

	void addEntries() override {
		addEntry("Sedan");
		addEntry("SUV");
		addEntry("Truck");
	}

	void printValue() override {
		cout << "차량 타입으로 " << getEntryWithIndex(getInput()) << "을 선택하셨습니다." << endl;
	}
};

class SelectEngineMenuStep : public MenuStep {
public:
	void setNickname() override {
		nickname = "엔진은";
	}
	void setStringBeforePrintingMenu() override {
		stringToPrintBeforeMenu.append("어떤 엔진을 탑재할까요?");
	}

	void setBackMenu() override {
		enableBackMenu();
	}

	void addEntries() override {
		addEntry("GM");
		addEntry("TOYOTA");
		addEntry("WIA");
		addEntry("고장난 엔진");
	}

	void printValue() override {
		cout << getEntryWithIndex(getInput()) << " 엔진을 선택하셨습니다." << endl;
	}
};

class SelectBrakeSystemMenuStep : public MenuStep {
public:
	void setNickname() override {
		nickname = "제동장치는";
	}
	void setStringBeforePrintingMenu() override {
		stringToPrintBeforeMenu.append("어떤 제동장치를 선택할까요?");
	}

	void setBackMenu() override {
		enableBackMenu();
	}

	void addEntries() override {
		addEntry("MANDO");
		addEntry("CONTINENTAL");
		addEntry("BOSCH");
	}

	void printValue() override {
		cout << getEntryWithIndex(getInput()) << "  제동장치를 선택하셨습니다." << endl;
	}
};

class SelectSteeringSystemMenuStep : public MenuStep {
public:
	void setNickname() override {
		nickname = "조향장치는";
	}
	void setStringBeforePrintingMenu() override {
		stringToPrintBeforeMenu.append("어떤 조향장치를 선택할까요?");
	}

	void setBackMenu() override {
		enableBackMenu();
	}

	void addEntries() override {
		addEntry("BOSCH");
		addEntry("MOBIS");
	}

	void printValue() override {
		cout << getEntryWithIndex(getInput()) << " 조향장치를 선택하셨습니다." << endl;
	}
};

class SelectRunTestMenuStep : public MenuStep {
	public:void setNickname() override {
		nickname = "Run/Test 메뉴는";
	}
	void setStringBeforePrintingMenu() override {
		stringToPrintBeforeMenu.append("멋진 차량이 완성되었습니다.\n");
		stringToPrintBeforeMenu.append("어떤 차량 타입을 선택할까요?");
	}

	void setBackMenu() override {
		enableBackMenu();
	}

	void addEntries() override {
		addEntry("RUN");
		addEntry("Test");
	}

	void printValue() override {
		
	}
};


class SelectCarTypeMenuStepFactory : public MenuStepFactory {
public:
	MenuStep* createMenuStep() override {
		MenuStep* menuStep = new SelectCarTypeMenuStep();
		menuStep->setNickname();
		menuStep->setStringBeforePrintingMenu();
		menuStep->addEntries();

		return menuStep;
	}
};

class SelectEngineMenuStepFactory : public MenuStepFactory {
public:
	MenuStep* createMenuStep() override {
		MenuStep* menuStep = new SelectEngineMenuStep();
		menuStep->setNickname();
		menuStep->setStringBeforePrintingMenu();
		menuStep->setBackMenu();
		menuStep->addEntries();

		return menuStep;
	}
};

class SelectBrakeSystemMenuStepFactory : public MenuStepFactory {
public:
	MenuStep* createMenuStep() override {
		MenuStep* menuStep = new SelectBrakeSystemMenuStep();
		menuStep->setNickname();
		menuStep->setStringBeforePrintingMenu();
		menuStep->setBackMenu();
		menuStep->addEntries();

		return menuStep;
	}
};

class SelectSteeringSystemMenuStepFactory : public MenuStepFactory {
public:
	MenuStep* createMenuStep() override {
		MenuStep* menuStep = new SelectSteeringSystemMenuStep();
		menuStep->setNickname();
		menuStep->setStringBeforePrintingMenu();
		menuStep->setBackMenu();
		menuStep->addEntries();

		return menuStep;
	}
};

class SelectRunTestMenuStepFactory : public MenuStepFactory {
public:
	MenuStep* createMenuStep() override {
		MenuStep* menuStep = new SelectRunTestMenuStep();
		menuStep->setNickname();
		menuStep->setStringBeforePrintingMenu();
		menuStep->setBackMenu();
		menuStep->addEntries();

		return menuStep;
	}
};
