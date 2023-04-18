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
	map<string, Category*> categories;
	int size = 0;

	public:
		Graph() {};

};