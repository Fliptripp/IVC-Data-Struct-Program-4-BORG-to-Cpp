#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
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

	int lookUp(string key)
	{
		int index = Hash(key);

		node* temp = hash[index];
		while (temp->number != NULL && temp->varName != "empty"){
			if (temp->varName == key)
				return temp->number;

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

//Linked Based Queue For Input
struct nodeQueue {
	string input;
	nodeQueue *next;
}*front = NULL, *rear = NULL;

void enQueue(string input)
{
	nodeQueue *temp = new nodeQueue;
	temp->input = input;
	temp->next = NULL;
	if (front == NULL && rear == NULL) {
		front = rear = temp;
		return;
	}
	rear->next = temp;
	rear = temp;
}

string deQueue() {
	nodeQueue *temp = new nodeQueue;
	string temparoni = "empty";
	if (front == rear) {
		temparoni = front->input;
		front = rear = NULL;
		return temparoni;
	}
	else {
		temparoni = front->input;
		front = front->next;
		return temparoni;
	}
}

bool isEmpty() {
	if (front == NULL)
		return true;
	else
		return false;
}


//Recursive functions
void manualBORG(HashTable a1, int n) 
{
	//Things done: COM(simply ignore input lol), reassigning values in the hash table, VAR, PRINT
	//Things not tested: START, the queue
	//This is assuming everything is perfect, hence no error checks anywhere
	string input = "empty", word, word2, varName, op = "empty";
	int num, num2;
	if (n == 0)
		cin.ignore();

		//Things to do:
		//Put this in queue and add pop to the end of while loop
		//Make a new queue in start to add the inputs needed to be removed once the nested scope is finished
		getline(cin, input);

		input = deQueue();
	while (input != "FINISH")
	{
		stringstream stream(input);
		while (getline(stream, word, ' ')) {
			if (word == "FINISH")
				break;
			//START Recursion
			else if (word == "START") {
				manualBORG(a1, n+1);
				break;
			}
			//COM
			else if (word == "COM")
				break;
			//VAR
			else if (word == "VAR") {
				stringstream stream(input);
				while (getline(stream, word2, ' ')) {
					if (isdigit(word2[0])) {
						stringstream ss;
						ss << word2;
						ss >> num;
					}
					else if (word2 != "VAR" && word2 != "=")
						varName = word2;
				}
				a1.addItems(varName, num);
				break;
			}
			//Print
			else if (word == "PRINT") {
				stringstream stream(input);
				while (getline(stream, word2, ' ')) {
					if (isdigit(word2[0]) && word2 != "PRINT" && (word2 != "*" || word2 != "+" || word2 != "-" || word2 != "/" || word2 != "%" || word2 != "^")) {
						stringstream ss;
						ss << word2;
						ss >> num2;
					}
					else if (word2 != "PRINT" && word2 != "*" && word2 != "+" && word2 != "-" && word2 != "/" && word2 != "%" && word2 != "^")
						varName = word2;
					else if (word2 == "*" || word2 == "+" || word2 == "-" || word2 == "/" || word2 == "%" || word2 == "^")
						op = word2;
				}
				num = a1.lookUp(varName);

				if (num == -1)
					cout << varName << " IS UNDEFINED\n";
				else {
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
						num = pow(num, num2);
					}
					cout << varName;
					if (op != "empty")
						cout << " " << op << " " << num2;
					cout << " IS " << num << endl;
				}
				op = "empty";
				break;
			}
			//Increment, Decrement, and Reassigning Values
			else {
				stringstream stream(input);
				while (getline(stream, word2, ' ')) {
					if (word2 != "--" && word2 != "++" && word2 != "=")
						varName = word2;
					else if (word2 == "--" || word2 == "++" || word2 == "=")
						op = word2;
					else if (isdigit(word2[0]) && (word2 != "--" || word2 != "++" || word2 != "=")) {
						stringstream ss;
						ss << word2;
						ss >> num2;
					}
				}
				num = a1.remove(varName);
				if (num == -1) { //Nothing is found
					cout << varName << " IS UNDEFINED\n";
				}
				else {
					if (op == "=")
						num = num2;
					else if (op == "++")
						num++;
					else if (op == "--")
						num--;
					a1.addItems(varName, num);
				}
				op = "empty";
				break;
			}
		}
		getline(cin, input);
	}
	return;
}

void fileBORG(HashTable a1)
{

}

void outputPrint()
{

}

int main()
{
	HashTable a2;
	int choice = 0;
	cout << "Program 4 BORG\n";
	cout << "-----------------------------------\n";
	cout << "1. Insert file with BORG commands\n";
	cout << "2. Manually insert BORG commands through console\n";
	cout << "-----------------------------------\n";
	cout << "Choice: ";
	cin >> choice;
	do {
		if (choice == 1)
		{
			fileBORG(a2);
		}

		else if (choice == 2)
		{
			cout << "\nManual Input Selected. Once Finished, type -1 to stop.\nBegin.\n";
			manualBORG(a2, 0);
		}
	} while (choice != 1 && choice != 2);

	return 0;
}
