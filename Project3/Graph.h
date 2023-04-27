#pragma once

#include "Cat.h"

class Category {
	string category;
	map<string, vector<Cat*>> subCategories;

public:
	Category() {};
	Category(string& category) {
		this->category = category;
	}
	map<string, vector<Cat*>>& getSubCategories() {
		return subCategories;
	}
	void insertCat(string& subCategory, Cat*& cat) {
		map<string, vector<Cat*>>::iterator iter = subCategories.begin();
		for (iter; iter != subCategories.end(); iter++) {
			if (iter->first == subCategory) {
				iter->second.push_back(cat); 
				break;
			}
		}
		if (iter == subCategories.end()) {
			vector<Cat*> v = {cat};
			subCategories.emplace(subCategory, v);
		}
	}
	void addToBreedList(string breed) {
		if (subCategories.find(breed) == subCategories.end()) {
			vector<Cat*> v;
			subCategories.emplace(breed, v);
		}
	}
};


class Graph {
	set<string> uniqueBreeds;
	map<string, Category*> categories;
	int catCount = 0;
	int categoryCount = 0;

public:
	Graph() {};
	~Graph();
	map<string, Category*>& getCategories();
	void insertCategory(string category);
	void insertCat(Cat*& cat);
	void addToBreedList(string& breed);
};
Graph::~Graph() {
	map<string, vector<Cat*>>::iterator iter = categories["breed"]->getSubCategories().begin();
	for (iter; iter != categories["breed"]->getSubCategories().end(); iter++) {
		for (int i = 0; i < iter->second.size(); i++) {
			delete iter->second.at(i);
		}
	}
	
	categories.clear();
}
map<string, Category*>& Graph::getCategories() {
	return this->categories;
}
void Graph::insertCategory(string category) {
	categoryCount += 1;
	Category* categoryContainer = new Category();
	categories.emplace(category, categoryContainer);
}
void Graph::addToBreedList(string& breed) {
	this->uniqueBreeds.insert(breed);
}
void Graph::insertCat(Cat*& cat) {
	this->catCount += 1;
	addToBreedList(cat->getBreed());

	map<string, Category*>::iterator iter = categories.begin();
	for (iter; iter != categories.end(); iter++) {
		string subCategory = "";
		if (iter->first == "age") {
			subCategory = cat->getAge();
		}
		else if (iter->first == "gender") {
			subCategory = cat->getGender();
		}
		else if (iter->first == "size") {
			subCategory = cat->getSize();
		}
		else if (iter->first == "coat") {
			subCategory = cat->getCoat();
		}
		else if (iter->first == "breed") {
			subCategory = cat->getBreed();
			iter->second->addToBreedList(cat->getBreed());
		}
		iter->second->insertCat(subCategory, cat);
	}
}