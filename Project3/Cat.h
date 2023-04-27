#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <Set>

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
};