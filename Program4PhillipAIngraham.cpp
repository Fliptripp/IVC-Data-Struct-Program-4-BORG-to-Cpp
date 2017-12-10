#include <iostream>
#include <fstream>
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
		
	}

	int Hash(string key) {

	}

	void addItem(string key, int num) {

	}
};