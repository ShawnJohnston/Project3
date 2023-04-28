#pragma once

#include "Structures.h"
#include <fstream>
#include <sstream>

class Menu {
	Graph* graph = new Graph();
	HashTable* table = new HashTable();

	string csvLocation = "cats.csv";
	set<string> uniqueBreeds;
	vector<Cat*> searchResults;

	void mainMenu();
	void filterMenu();
	void dataMenu();
	void completionMenu(bool& searching, string& category, string& subCategory);
	 
	void processFileInput();
	void overwriteGraph();
	void search(string& critera, string& subCriteria);
	void searchHelper(string& category, string& subCategory, vector<string> subCategories);
	void insert(string& item, int order, int id, string age, string gender, string size, string coat, string breed);
	void saveToFile(pair<string, string> criteria);
public:
	Menu() {
		graph->insertCategory("age");
		graph->insertCategory("gender");
		graph->insertCategory("size");
		graph->insertCategory("coat");
		graph->insertCategory("breed");

		cout << "Welcome to the Cat Image Link Filter Tool" << endl << endl << 
			"Loading data... This will take about 1 minute. Consider taking this time to pet your actual cat." << endl;
		processFileInput();
		cout << "Finished!" << endl << endl;

		mainMenu();
	}
};

void Menu::mainMenu() {
	string input = "";

	while (input != "1" || input != "2" || input != "3") {
			cout << "1. Search" << endl <<
					"2. Load Data" << endl <<
					"3. Exit" << endl << endl;

		cin >> input;

		if (input == "1") {
			filterMenu();
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
	bool fileWasChanged = false;

	while (input != "1" || input != "2" || input != "3") {
		cout << "1. Default" << endl <<
			"2. Upload" << endl <<
			"3. Back" << endl << endl;

		cin >> input;

		if (input == "3") {
			return;
		}
		else if (input == "1") {
			if (csvLocation != "cats.csv") {
				fileWasChanged = true;
				csvLocation = "cats.csv";
			}

			cout << "Loading data... This will take about 30 seconds. Consider taking this time to pet your actual cat." << endl;
			processFileInput();
			cout << "Finished!" << endl << endl;
		}
		else if (input == "2") {
			cout << "Type the name of the data file you'd like to use." << endl <<
				"You must follow these instructions for the custom file to work properly: " << endl <<
				"1.	The file must be within the program folder if you just want to type the file. Otherwise you have to use the absolute path." << endl <<
				"2. You have to include the name of the file as well as the \".csv\" file extension. The default file is 'cats.csv'." << endl <<
				"3.	The csv file must follow this format for each column: (columns 3 and 4 are junk, whatever you put there is ignored)" << endl <<
				"	order,id,junk,junk,age,gender,size,coat,breed,hyperlink" << endl <<
				"4.	Any row can store multiple hyperlinks, however, all hyperlink columns must start with \" 'full': '\" in order for them to be acknowledged as such." << endl <<
				"	This is a consequence of the original csv file being poorly organized and also including multiple sizes for the same photos." << endl << endl;
			string newCSV = "";
			cin >> newCSV;
			if (csvLocation.substr(csvLocation.length() - 4, csvLocation.length()) != ".csv") {
				cout << "Your input must end in '.csv'. Upload rejected." << endl << endl;
			}
			else {
				csvLocation = newCSV;
				fileWasChanged = true;
			}
		}
		if (fileWasChanged) {
			overwriteGraph();
			break;
		}
	}
}
void Menu::filterMenu() {
	//	Criteria Code
	// age,gender,size,coat,breed
	string input = ""; 
	string category, subCategory;

	bool selecting = false;

	cout << "Select from the following search criteria. " << endl <<
		"1. Age Group" << endl <<
		"2. Gender" << endl <<
		"3. Size" << endl <<
		"4. Coat" << endl <<
		"5. Breed" << endl << endl;

	while (input != "1" || input != "2" || input != "3" || input != "4" || input != "5") {
		cin >> input;

		if (input == "1") {
			category = "age";
			vector<string> ageCategories = { "Baby", "Young", "Adult", "Senior" };
			searchHelper(category, subCategory, ageCategories);
			break;
		}
		else if (input == "2") {
			category = "gender";
			subCategory = "";
			string subInput = "";
			while (subInput != "1" || subInput != "2") {
				cout << "Male or Female?" << endl <<
					"1. Male" << endl <<
					"2. Female" << endl << endl;
				cin >> subInput;
				switch (stoi(subInput)) {
				case 1:
					subCategory = "Male";
					break;
				case 2:
					subCategory = "Female";
					break;
				default:
					subCategory = "";
					cout << "Select a valid option." << endl << endl;
					break;
				}
				if (subCategory != "") {
					break;
				}
			}
			break;
		}
		else if (input == "3") {
			category = "size";
			vector<string> sizeCategories = { "Small", "Medium", "Large", "Extra Large" };
			searchHelper(category, subCategory, sizeCategories);
			break;
		}
		else if (input == "4") {
			category = "coat";
			vector<string> coatCategories = { "Hairless", "Short", "Medium", "Long" };
			searchHelper(category, subCategory, coatCategories);
			break;
		}
		else if (input == "5") {
			category = "breed";
			string subInput = "";
			while (subInput == "") {
				cout << "What breed are you looking for?" << endl;

				string breed;
				int counter = 1;
				set<string>::iterator iter = uniqueBreeds.begin();
				for (iter; iter != uniqueBreeds.end(); iter++) {
					cout << counter << ".	" << *iter << endl;
					counter++;
				}

				cin >> subInput;
				iter = uniqueBreeds.begin();
				for (size_t i = 0; i < stoi(subInput) - 1; i++) {
					iter++;
				}
				subCategory = *iter;

				if (subCategory != "") {
					break;
				}
				else {
					cout << "Select a valid option." << endl << endl;
				}
			}
			break;
		}
	}

	search(category, subCategory);

	bool searching = true;
	completionMenu(searching, category, subCategory);
	while (searching) {
		filterMenu();
		if (!searching) {
			return;
		}
	}
}
void Menu::completionMenu(bool& searching, string& category, string& subCategory) {
	subCategory.at(0) = char(subCategory.at(0) + 32);
	cout << "Search Complete." << endl <<
		category << " -> " << subCategory << endl <<
		table->getSize() << " photos found." << endl << endl;
	string input = "";

	while (input != "1" || input != "2" || input != "3") {
		cout << "1. New Search" << endl <<
			"2. Save to File" << endl <<
			"3. Main Menu" << endl << endl;

		cin >> input;

		if (input == "1") {
			searchResults.clear();
			table = new HashTable();
			return;
		}
		else if (input == "2") {
			saveToFile(pair<string, string>(category, subCategory));

			searchResults.clear();
			table = new HashTable();
			searching = false;
			return;
		}
		else if (input == "3") {
			searchResults.clear();
			table = new HashTable();
			searching = false;
			return;
		}
	}

}
void Menu::processFileInput() {
	ifstream file;
	file.open(csvLocation);

	string line;
	string item;

	if (!file.eof()) {
		while (getline(file, line)) {


			stringstream ss(line);

			int order, id;
			string age, gender, size, coat, breed;

			int counter = 0;
			while (getline(ss, item, ',')) {
				if (item == "order") {
					break;
				}

				switch (counter) {
				case 0:
					order = stoi(item);
					break;
				case 1:
					id = stoi(item);
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					age = item;
					break;
				case 5:
					gender = item;
					break;
				case 6:
					size = item;
					break;
				case 7:
					coat = item;
					break;
				case 8:
					uniqueBreeds.insert(item);
					breed = item;
				default:
					if (item.substr(0, 7) == " 'full'") {
						insert(item, order, id, age, gender, size, coat, breed);
					}
					break;
				}

				counter++;
			}
		}
	}
	file.close();
}
void Menu::overwriteGraph() {
	delete graph;
	graph = new Graph();
	uniqueBreeds.clear();

	cout << "Loading data... This will take about 30 seconds. Consider taking this time to pet your actual cat." << endl;
	processFileInput();
	cout << "Finished!" << endl << endl;
}
void Menu::search(string& criteria, string& subCriteria) {
	searchResults = graph->getCategories()[criteria]->getSubCategories()[subCriteria];

	for (size_t i = 0; i < graph->getCategories()[criteria]->getSubCategories()[subCriteria].size(); i++) {
		
		Cat* cat = graph->getCategories()[criteria]->getSubCategories()[subCriteria].at(i);
		table->insert(cat->getId(), cat);
	}
}
void Menu::searchHelper(string& category, string& subCategory, vector<string> subCategories) {
	string subInput = "";
	while (subInput != "1" || subInput != "2" || subInput != "3" || subInput != "4") {
		cout << "How big should are the cats?" << endl <<
			"1. " << subCategories.at(0) << endl <<
			"2. " << subCategories.at(1) << endl <<
			"3. " << subCategories.at(2) << endl <<
			"4. " << subCategories.at(3) << endl << endl;
		cin >> subInput;
		switch (stoi(subInput)) {
		case 1:
			subCategory = subCategories.at(0);
			break;
		case 2:
			subCategory = subCategories.at(1);
			break;
		case 3:
			subCategory = subCategories.at(2);
			break;
		case 4:
			subCategory = subCategories.at(3);
			break;
		default:
			subCategory = "";
			cout << "Select a valid option." << endl << endl;
			break;
		}
		if (subCategory != "") {
			break;
		}
	}
}
void Menu::insert(string& item, int order, int id, string age, string gender, string size, string coat, string breed) {
	int trimLength = 0;
	for (size_t i = item.length() - 1; i > 0; i--) {
		char index = item.at(i);
		if (index < 48 || index > 57) {
			trimLength++;
		}
		else {
			break;
		}
	}
	string cleanLink = item.substr(10, item.length());
	cleanLink = cleanLink.substr(0, cleanLink.length() - trimLength);
	Cat* cat = new Cat(order, id, age, gender, size, coat, breed, cleanLink);
	graph->insertCat(cat);
}
void Menu::saveToFile(pair<string, string> criteria) {
	ofstream file;
	string fileName = criteria.first + "_" + criteria.second + ".csv";
	file.open(fileName);
	int counter = 0;
	for (size_t i = 0; i < table->getCapacity(); i++) {
		if (!table->get()[i].empty()) {
			file << counter << "," << table->get()[i].front()->getPhoto() << endl;
			counter++;
		}
	}
}