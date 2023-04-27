#pragma once

#include "Structures.h"
#include <fstream>
#include <sstream>

class Menu {
	Graph* graph = new Graph();
	HashTable* table = new HashTable();

	string csvLocation = "asdf.csv";
	set<string> uniqueBreeds;
	vector<Cat*> searchResults;

	void mainMenu();
	void searchMenu();
	void dataMenu();
	void completionMenu(bool& searching);
	 
	void processFileInput();
	void overwriteGraph();
	void search(string& critera, string& subriteria);
	void saveToFile();
public:
	Menu() {
		graph->insertCategory("age");
		graph->insertCategory("gender");
		graph->insertCategory("size");
		graph->insertCategory("coat");
		graph->insertCategory("breed");

		cout << "Welcome to the Cat Image Link Filter Tool" << endl << endl << 
			"Loading data... This will take about 30 seconds. Consider taking this time to pet your actual cat." << endl;
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
void Menu::searchMenu() {
	//	Criteria Code
	// age,gender,size,coat,breed
	string input = "";
	string criteria, subcriteria;

	bool selecting = false;

	while (input != "1" || input != "2" || input != "3" || input != "4" || input != "5" || input != "6") {
		cout << "Select from the following search critera. " << endl <<
			"1. Age Group" << endl <<
			"2. Gender" << endl <<
			"3. Size" << endl <<
			"4. Coat" << endl <<
			"5. Breed" << endl << endl;

		cin >> input;

		string subInput = "";
		if (input == "1") {
			criteria = "age";
			while (subInput != "1" || subInput != "2" || subInput != "3" || subInput != "4") {
				cout << "How old should the cats be, generally?" << endl <<
					"1. Baby" << endl <<
					"2. Young" << endl <<
					"3. Adult" << endl <<
					"4. Senior" << endl << endl;
				cin >> subInput;
				switch (stoi(subInput)) {
				case 1:
					subcriteria = "Baby";
					break;
				case 2:
					subcriteria = "Young";
					break;
				case 3:
					subcriteria = "Adult";
					break;
				case 4:
					subcriteria = "Senior";
					break;
				default:
					subcriteria = "";
					break;
				}
				if (subcriteria != "") {
					break;
				}
			}
		}
		else if (input == "2") {
			criteria = "gender";
			while (subInput != "1" || subInput != "2") {
				cout << "Should the cats be male or female?" << endl <<
					"1. Male" << endl <<
					"2. Female" << endl << endl;
				cin >> subInput;
				if (subInput == "1") {
					subcriteria = "Male";
				}
				else if (subInput == "2") {
					subcriteria = "Female";
				}
				if (subcriteria != "") {
					break;
				}
			}
		}
		else if (input == "3") {
			criteria = "size";
			while (subInput != "1" || subInput != "2" || subInput != "3" || subInput != "4") {
				cout << "How big should are the cats?" << endl <<
					"1. Small" << endl <<
					"2. Medium" << endl <<
					"3. Large" << endl <<
					"4. Extra Large" << endl << endl;
				cin >> subInput;
				switch (stoi(subInput)) {
				case 1:
					subcriteria = "Small";
					break;
				case 2:
					subcriteria = "Medium";
					break;
				case 3:
					subcriteria = "Large";
					break;
				case 4:
					subcriteria = "Extra Large";
					break;
				default:
					subcriteria = "";
					break;
				}
				if (subcriteria != "") {
					break;
				}
			}
		}
		else if (input == "4") {
			criteria = "coat";
			while (subInput != "1" || subInput != "2" || subInput != "3") {
				cout << "How long should the coat length be?" << endl <<
					"1.	Hairless" << endl <<
					"2.	Short" << endl <<
					"3.	Medium" << endl <<
					"4.	Long" << endl << endl;
				cin >> subInput;
				switch (stoi(subInput)) {
				case 1:
					subcriteria = "Hairless";
					break;
				case 2:
					subcriteria = "Short";
					break;
				case 3:
					subcriteria = "Medium";
					break;
				case 4:
					subcriteria = "Long";
					break;
				default:
					subcriteria = "";
					break;
				}
				if (subcriteria != "") {
					break;
				}
			}
		}
		else if (input == "5") {
			criteria = "breed";
			while (subInput != "1" || subInput != "2" || subInput != "3") {
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
				subcriteria = *iter;

				cout << subcriteria << endl << endl;

				if (subcriteria != "") {
					break;
				}
			}
		}
		cout << endl << endl;


		if (subcriteria != "") {
			break;
		}
	}
	  
	search(criteria, subcriteria);

	bool searching = true;
	completionMenu(searching);
	while (searching) {
		searchMenu();
	}
}
void Menu::completionMenu(bool& searching) {
	cout << "Search Complete." << endl <<
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
			saveToFile();

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

	vector<Cat*> collection;

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
						collection.push_back(cat);
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
void Menu::saveToFile() {
	ofstream file;
	file.open("links.txt");
	for (size_t i = 0; i < table->getCapacity(); i++) {
		if (!table->get()[i].empty()) {
			//cout << table->get()[i].front()->getPhoto() << endl;
			file << table->get()[i].front()->getPhoto() << endl;
		}
	}
}