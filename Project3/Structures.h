#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <Set>
#include <forward_list>

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
	int& getOrder() {
		return this->order;
	}
	int& getId() {
		return this->id;
	}
	string& getAge() {
		return this->age;
	}
	string& getGender() {
		return this->gender;
	}
	string& getSize() {
		return this->size;
	}
	string& getCoat() {
		return this->coat;
	}
	string& getBreed() {
		return this->breed;
	}
	string& getPhoto() {
		return photo;
	}
};



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



class HashTable {
	forward_list<Cat*>* table = new forward_list<Cat*>[10000];
	long long size = 0;
	long long capacity = 10000;


public:
	HashTable();
	forward_list<Cat*>* get();
	long long getSize();
	long long getCapacity();
	void insert(int& key, Cat*& cat);
	int hashFunction(int& key);
	void quadraticProbe(int& index, Cat*& cat);
	void checkToRehash();
	void rehash(const long long& capacity);
};
HashTable::HashTable() {
	for (size_t i = 0; i < capacity; i++) {
		forward_list<Cat*>* list = new forward_list<Cat*>;
		table[i] = *list;
	}
}
forward_list<Cat*>* HashTable::get() {
	return table;
}
long long HashTable::getSize() {
	return this->size;
}
long long HashTable::getCapacity() {
	return this->capacity;
}
void HashTable::insert(int& key, Cat*& cat) {
	int index = hashFunction(key);

	if (table[index].empty()) {
		table[index].push_front(cat);
		size++;
		checkToRehash();
	}
	else {
		quadraticProbe(index, cat);
		size++;
		checkToRehash();
	}
}
int HashTable::hashFunction(int& key) {
	string keyString = to_string(key);
	int hash = 0;

	for (size_t i = 0; i < keyString.length(); i++) {
		hash += char(keyString.at(i));
	}

	return (hash % capacity);
}
void HashTable::quadraticProbe(int& index, Cat*& cat) {
	if (index >= capacity) {
		index -= capacity;
	}
	long long counter = 1;
	while (!table[index].empty()) {
		index += (counter * counter);
		if (index >= capacity) {
			while (index >= capacity) {
				index -= capacity;
			}
		}
		if (table[index].empty()) {
			table[index].push_front(cat);
			break;
		}
		counter++;
	}
}
void HashTable::checkToRehash() {
	if (((double)size / (double)capacity) >= .7) {
		rehash(capacity);
	}
}
void HashTable::rehash(const long long& capacity) {
	int newCapacity = capacity * 2;
	forward_list<Cat*>* newTable = new forward_list<Cat*>[newCapacity];
	for (size_t i = 0; i < newCapacity; i++) {
		if (i < capacity) {
			newTable[i] = table[i];
		}
		else {
			forward_list<Cat*>* list = new forward_list<Cat*>;
			newTable[i] = *list;
		}
	}
	this->capacity *= 2;
	table = newTable;
}