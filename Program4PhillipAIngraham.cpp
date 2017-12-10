#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

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
		for (unsigned int i = 0; i < key.length(); i++) { //(number ascii value * position in string[added as many as letters there are in the string]) % tableSize
			index = (unsigned int)key[i] * (i + 1); // hope this works
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

	int lookUp(string key, int num)
	{
		int index = Hash(key);

		node* temp = hash[index];
		while (temp->number != NULL && hash[index]->varName == "empty"){
			if (temp->number == num && temp->varName == key)
				return num;

			else
				temp = temp->next;
		}

		return -1;
	}

	int remove(string key)
	{
		int index = Hash(key);
		int temp = 0;

		node* delPtr = NULL;
		node* P1 = NULL;
		node* P2 = NULL;

		if (hash[index]->varName == "empty" && hash[index]->number == NULL)//there is nothing in the bucket and the user is asking for the impossible
		{
			return -1;
		}

		else if (hash[index]->varName == key && hash[index]->next == NULL) { //there is only one thing in the bucket
			temp = hash[index]->number;
			hash[index]->varName = "empty";
			hash[index]->number = NULL;
			return temp;
		}

		else if (hash[index]->varName == key) { //First item but things after first item
			temp = hash[index]->number;
			delPtr = hash[index]->next;
			hash[index] = hash[index]->next;
			delete delPtr;
		}

		else { //The item is not in the first slot, so we must search
			P1 = hash[index]->next;
			P2 = hash[index];
		}
		while (P1 != NULL && P1->varName != key) {
			P2 = P1;
			P1 = P1->next;
		}

		if (P1 == NULL) //No match
			return -1;
		
		else { //Item found
			temp = P1->number;
			delPtr = P1;
			P1 = P1->next;
			P2->next = P1;
			delete delPtr;

			return temp;
		}
			
	}
};


//Recursive functions


void manualBORG(HashTable a1) 
{
	//Things done: COM(simply ignore input lol)
	//Things not tested: START, VAR, PRINT, reassigning values in the hash table
	//This is assuming everything is perfect, hence no error checks anywhere
	string input, word, varName, op = "empty";
	int num, num2;
	getline(cin, input);
	while (input != "FINISH")
	{
		if (input == "START") //START
			manualBORG(a1);

		else if (input[0] == 'V' && input[1] == 'A' && input[2] == 'R') { //VAR
			stringstream stream(input);
			while (getline(stream, word, ' ')) {
				if (isdigit(word[0]) && word != "VAR" && word != "="){
					stringstream ss;
					ss << word;
					ss >> num;
				}
				else if (word != "VAR" && word != "=") {
					varName = word;
				}
			}
			a1.addItems(varName, num);
		}

		else if (input[0] == 'P' && input[1] == 'R' && input[2] == 'I' && input[3] == 'N' && input[4] == 'T') { //PRINT
			stringstream stream(input);
			while (getline(stream, word, ' ')) {
				if (isdigit(word[0]) && word != "PRINT" && (word != "*" || word != "+" || word != "-" || word != "/" || word != "%" || word != "^")) {
					stringstream ss;
					ss << word;
					ss >> num2;
				}
				else if (word != "PRINT" && (word != "*" || word != "+" || word != "-" || word != "/" || word != "%" || word != "^")) {
					varName = word;
				}
				else if (word == "*" || word == "+" || word == "-" || word == "/" || word == "%" || word == "^") {
					op = word;
				}
			}
			num = a1.lookUp(varName, num);

			if (num == -1) { //Nothing is found
				cout << varName << " IS UNDEFINED\n";
				break;
			}

			if (op == "+") {
				num = num + num2;
			}
			else if (op == "-") {
				num = num - num2;
			}
			else if (op == "*") {
				num = num * num2;
			}
			else if (op == "/") {
				num = num / num2;
			}
			else if (op == "%") {
				num = num % num2;
			}
			else if (op == "^") {
				num = num ^ num2;
			}
			cout << varName;
			if (op != "empty")
				cout << " " << op << " " << num2;
			cout << "IS " << num;
			op = "empty";
		}

		else { //Increment, decrement, and reassigning values
			stringstream stream(input);
			while (getline(stream, word, ' ')) {
				if (word != "--" || word != "++" || word != "=")
					varName = word;
				else if (word == "--" || word == "++" || word == "=")
					op = word;
				else if (isdigit(word[0]) && (word != "--" || word != "++" || word != "=")) {
					stringstream ss;
					ss << word;
					ss >> num2;
				}
			}

			num = a1.remove(varName);
			if (num == -1) { //Nothing is found
				cout << varName << " IS UNDEFINED\n";
				break;
			}

			else if (op == "=")
				num = num2;
			else if (op == "++")
				num++;
			else if (op == "--")
				num--;

			a1.addItems(varName, num);
		}
		getline(cin, input);
	}
	return;
}

void fileBORG(HashTable a1)
{

}

int main()
{
	HashTable a1;
	int choice = 0;
	cout << "Program 4 BORG\n";
	cout << "-----------------------------------\n";
	cout << "1. Insert file with BORG commands\n";
	cout << "2. Manually insert BORG commands through console\n";
	cout << "Choice: ";
	cin >> choice;
	do {
		if (choice == 1)
		{
			fileBORG(a1);
		}

		else if (choice == 2)
		{
			cout << "\nManual Input Selected. Begin.\n";
			string inputFalse;
			cin >> inputFalse; //Should be START
			manualBORG(a1);
		}
	} while (choice != 1 && choice != 2);

	return 0;
}
