#include <iostream>
#include <fstream>
#include <string>
using namespace std;


/*
	Use the first letter in the variable name to determine where the the value of the variable and the name will go
*/
class HashTable
{
private:
	static const int tableSize = 27; //27 Letters in the alphabet

	struct node {
		int number;
		string varName;
		node* next;
	};

	node* hash[tableSize];

public:
	HashTable() {
		for (int i = 0; i < tableSize; i++) {
			hash[i] = new node;
			hash[i]->number = NULL;
			hash[i]->varName = "empty";
			hash[i]->next = NULL;
		}
	}

	int Hash(string key) {
		int index = 0;
		for (int i = 0; i < key.length; i++) {
			index = (int)key[i] * (i + 1);
		}
		index = index % tableSize;
		return index;

	}

	void addItem(string key, int num) {

	}
};