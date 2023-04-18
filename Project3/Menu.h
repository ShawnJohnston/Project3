#pragma once

#include "Graph.h"

class Menu {
	Graph* graph;
	string csvLocation = "";

	void mainMenu();
	void searchMenu();
	void dataMenu();
	void completionMenu(bool& searching);

	void processFileInput();
	void saveToFile();
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
void Menu::dataMenu() {
	cout << "Use the default data file or upload your own." << endl << endl;

	string input = "";

	while (input != "1" || input != "2" || input != "3") {
		cout << "1. Default" << endl <<
			"2. Upload" << endl <<
			"3. Back" << endl << endl;

		cin >> input;

		if (input == "1") {
			//	Set csvLocation to 'cats.csv' in Resources folder.
		}
		else if (input == "2") {
			//	Set csvLocation to some other csv file.
		}
		else if (input == "3") {
			break;
		}
	}
}
void Menu::searchMenu() {
	// Criteria Code

	//	Search Function

	//	Sort Function

	bool searching = true;
	while (searching) {
		completionMenu(searching);
	}
}
void Menu::completionMenu(bool& searching) {
	cout << "Search Complete." << endl << endl;
	string input = "";

	while (input != "1" || input != "2" || input != "3") {
		cout << "1. New Search" << endl <<
			"2. Save to File" << endl <<
			"3. Main Menu" << endl << endl;

		cin >> input;

		if (input == "1") {
			return;
		}
		else if (input == "2") {
			saveToFile();

			searching = false;
			return;
		}
		else if (input == "3") {
			searching = false;
			return;
		}
	}

}
void Menu::saveToFile() {

}