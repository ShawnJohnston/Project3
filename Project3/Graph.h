#pragma once

#include <string>

using namespace std;

class Node {
	// order,id,url,type,age,gender,size,coat,breed,photos,med_photos

	int order;
	int id;
	string age;
	string gender;
	string size;
	string coat;
	string breed;
	string photo;

	Node() {

	}
	Node(int& order, int& id, string& age, string& gender, string& size, string& coat, string& breed, string& photo) {
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