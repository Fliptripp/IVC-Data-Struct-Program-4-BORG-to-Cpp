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
		for (int i = 0; i < key.length; i++) { //(number ascii value * position in string[added as many as letters there are in the string]) % tableSize
			index = (int)key[i] * (i + 1);
		}
		index = index % tableSize;
		return index;
	}

	void addItems(string key, int num) {
		int index = Hash(key);

		if (hash[index]->number == NULL && hash[index]->varName == "empty") {
			hash[index]->number = num;
			hash[index]->varName = key;
		}

		else {
			node* head = hash[index];
			node* temp = new node;
			temp->number = num;
			temp->varName = key;
			temp->next = NULL;

			while (head->next != NULL)
				head = head->next;

			head->next = temp;
		}
	}
};