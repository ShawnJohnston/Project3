#pragma once

#include <string>
#include <map>
#include <Set>
#include <vector>

using namespace std;

class Cat {
	int order = -1;
	int id = -1;
	string age = "";
	string gender = "";
	string size = "";
	string coat = "";
	string breed = "";
	string photo = "";

	bool accessed = false;

public:
	Cat() {}
	Cat(int& order, int& id, string& age, string& gender, string& size, string& coat, string& breed, string& photo) {
		this->order = order;
		this->id = id;
		this->age = age;
		this->gender = gender;
		this->size = size;
		this->coat = coat;
		this->breed = breed;
		this->photo = photo;
	}
};

class Category {
	string category;
	set<string> uniqueBreeds;
	map<string, vector<Cat*>> subCategories;
	vector<Cat*> cats;

public:
	Category() {};
	Category(string& category) {
		this->category = category;

		vector<Cat*> v;
		vector<Cat*> v1;
		vector<Cat*> v2;
		vector<Cat*> v3;
		if (this->category == "age") {
			subCategories.emplace("Baby", v);
			subCategories.emplace("Young", v1);
			subCategories.emplace("Adult", v2);
			subCategories.emplace("Senior", v3);
		}
		else if (this->category == "gender") {
			subCategories.emplace("Male", v);
			subCategories.emplace("Female", v1);
		}
		else if (this->category == "size") {
			subCategories.emplace("Small", v);
			subCategories.emplace("Medium", v1);
			subCategories.emplace("Large", v2);
			subCategories.emplace("Extra Large", v3);
		}
		else if (this->category == "coat") {
			subCategories.emplace("Short", v);
			subCategories.emplace("Medium", v1);
			subCategories.emplace("Long", v2);
		}
		else if (this->category == "breed") {
			set<string>::iterator iter = uniqueBreeds.begin();
			for (iter; iter != uniqueBreeds.end(); iter++) {
				vector<Cat*> v4;
				subCategories.emplace(*iter, v4);
			}
		}

	}
	void insertCat(Cat*& cat) {
		cats.push_back(cat);
	}
	void importBreedList(set<string>& breeds) {
		this->uniqueBreeds = breeds;
	}
};


class Graph {
	map<int, Cat*> cats;
	map<string, Category*> categories;
	int catCount = 0;
	int categoryCount = 0;

	void categorizeInsertedCat(Cat*& cat);
public:
	Graph() {};
	void insertCategory(string category, set<string>& uniqueBreeds);
	void insertCat(Cat*& cat);
};

void Graph::insertCategory(string category, set<string>& uniqueBreeds) {
	categoryCount += 1;
	Category* categoryObj = new Category();
	categoryObj->importBreedList(uniqueBreeds);
	categories.emplace(category, categoryObj);
}
void Graph::insertCat(Cat*& cat) {
	this->catCount += 1;
	this->cats.emplace(catCount, cat);

	categorizeInsertedCat(cat);
}
void Graph::categorizeInsertedCat(Cat*& cat) {

}