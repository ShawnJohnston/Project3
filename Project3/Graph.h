#pragma once

#include <string>
#include <map>
#include <vector>

using namespace std;

class Cat {
	// order,id,url,type,age,gender,size,coat,breed,photos,med_photos

	int order = -1;
	int id = -1;
	string age = "";
	string gender = "";
	string size = "";
	string coat = "";
	string breed = "";
	string photo = "";

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
	vector<Cat*> cats;

public:
	Category() {};
	Category(string& category) {
		this->category = category;
	}
	void insertCat(Cat*& cat) {
		cats.push_back(cat);
	}
};


class Graph {
	map<int, Cat*> cats;
	map<int, Category*> categories;
	int catCount = 0;
	int categoryCount = 0;

	void categorizeInsertedCat(Cat*& cat);
public:
	Graph() {};
	void insertCategory(string& category);
	void insertCat(Cat*& cat);
};

//void Graph::insertCategory(string& category) {
//	categoryCount += 1;
//	categories.emplace(categoryCount, category);
//}
//void Graph::insertCat(Cat*& cat) {
//	this->catCount += 1;
//	this->cats.emplace(catCount, cat);
//
//	categorizeInsertedCat(cat);
//}
//void Graph::categorizeInsertedCat(Cat*& cat) {
//
//}