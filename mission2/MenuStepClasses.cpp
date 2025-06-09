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
			cout << "ERROR :: " << nickname << " " << getRangeMin() << " ~ " << getRangeMax() << " ������ ���� ����" << endl;
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
		// Range�� ��� 0 (�ڷ�/��ó������ ����)�� �����Ѵ�.
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

	void enableBackMenu(string backMenuString_ = "�ڷΰ���")
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
		nickname = "���� Ÿ����";
	}
	void setStringBeforePrintingMenu() override {
		stringToPrintBeforeMenu.append("        ______________\n");
		stringToPrintBeforeMenu.append("       /|            | \n");
		stringToPrintBeforeMenu.append("  ____/_|_____________|____\n");
		stringToPrintBeforeMenu.append(" |                      O  |\n");
		stringToPrintBeforeMenu.append(" '-(@)----------------(@)--'\n");
		stringToPrintBeforeMenu.append("===============================\n");
		stringToPrintBeforeMenu.append("� ���� Ÿ���� �����ұ��?");
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
		cout << "���� Ÿ������ " << getEntryWithIndex(getInput()) << "�� �����ϼ̽��ϴ�." << endl;
	}
};

class SelectEngineMenuStep : public MenuStep {
public:
	void setNickname() override {
		nickname = "������";
	}
	void setStringBeforePrintingMenu() override {
		stringToPrintBeforeMenu.append("� ������ ž���ұ��?");
	}

	void setBackMenu() override {
		enableBackMenu();
	}

	void addEntries() override {
		addEntry("GM");
		addEntry("TOYOTA");
		addEntry("WIA");
		addEntry("���峭 ����");
	}

	void printValue() override {
		cout << getEntryWithIndex(getInput()) << " ������ �����ϼ̽��ϴ�." << endl;
	}
};

class SelectBrakeSystemMenuStep : public MenuStep {
public:
	void setNickname() override {
		nickname = "������ġ��";
	}
	void setStringBeforePrintingMenu() override {
		stringToPrintBeforeMenu.append("� ������ġ�� �����ұ��?");
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
		cout << getEntryWithIndex(getInput()) << "  ������ġ�� �����ϼ̽��ϴ�." << endl;
	}
};

class SelectSteeringSystemMenuStep : public MenuStep {
public:
	void setNickname() override {
		nickname = "������ġ��";
	}
	void setStringBeforePrintingMenu() override {
		stringToPrintBeforeMenu.append("� ������ġ�� �����ұ��?");
	}

	void setBackMenu() override {
		enableBackMenu();
	}

	void addEntries() override {
		addEntry("BOSCH");
		addEntry("MOBIS");
	}

	void printValue() override {
		cout << getEntryWithIndex(getInput()) << " ������ġ�� �����ϼ̽��ϴ�." << endl;
	}
};

class SelectRunTestMenuStep : public MenuStep {
	public:void setNickname() override {
		nickname = "Run/Test �޴���";
	}
	void setStringBeforePrintingMenu() override {
		stringToPrintBeforeMenu.append("���� ������ �ϼ��Ǿ����ϴ�.\n");
		stringToPrintBeforeMenu.append("� ���� Ÿ���� �����ұ��?");
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
