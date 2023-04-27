#pragma once

#include "Cat.h"

#include <forward_list>

class HashTable {
	forward_list<Cat*>* table[10000];
	int size = 0;
	int capacity = 10000;


public:
	HashTable();
	void insert(int& key, Cat*& cat);
	int hashFunction(int& key);
	void quadraticProbe(int& index, Cat*& cat);
	void checkToRehash();
	void rehash(const int& capacity);
};
HashTable::HashTable() {
	for (size_t i = 0; i < capacity; i++) {
		forward_list<Cat*>* list = new forward_list<Cat*>;
		table[i] = list;
	}
}
void HashTable::insert(int& key, Cat*& cat) {
	int index = hashFunction(key);

	if (size == capacity) {
		table[index]->push_front(cat);
	}

	if (table[index]->empty()) {
		table[index]->push_front(cat);
	}
	else {
		quadraticProbe(index, cat);
	}
	size++;
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
	if (((float)size / (float)capacity) < .7) {
		int counter = 1;
		while (!table[index]->empty()) {
			index += (counter * counter);
			if (table[index]->empty()) {
				table[index]->push_front(cat);
				size++;
				break;
			}

			if (index >= capacity) {
				index -= capacity;
			}
			counter++;
		}
	}
}
void HashTable::checkToRehash() {
	if (((float)size / (float)capacity) < .7) {
		rehash(capacity);
	}
}
void HashTable::rehash(const int& capacity) {
	int newCapacity = capacity * 2;
	forward_list<Cat*>* newTable = new forward_list<Cat*>[newCapacity];
	for (size_t i = 0; i < capacity; i++) {
		newTable[i] = *table[i];
	}
	this->capacity *= 2;
	*table = newTable;
}