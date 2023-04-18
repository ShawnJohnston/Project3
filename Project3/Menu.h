#pragma once

#include "Graph.h"

class Menu {

	void mainMenu();
	void searchMenu();
	void dataMenu();
	void completionMenu();

	void compileGraph();
public:
	Menu() {
		mainMenu();
	}
};

void Menu::mainMenu() {
	cout << "Welcome to the Cat Image Link Filter Tool" << endl << endl;

	string input = "";

	while (input != "1" || input != "2" || input != "3") {
			cout << "1. Search" << endl <<
					"2. Load Data" << endl <<
					"3. Exit" << endl << endl;

		cin >> input;

		if (input == "1") {
			searchMenu();
		}
		else if (input == "2") {
			dataMenu();
		}
		else if (input == "3") {
			break;
		}

		cout << endl << endl;
	}


}
void Menu::searchMenu() {

}
void Menu::dataMenu() {

}