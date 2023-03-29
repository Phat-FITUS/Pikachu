#include "User.h"
#include <iostream>
#include <fstream>
using namespace std;

LeaderBoard::LeaderBoard() {
	//Initial list
	this->head = NULL;
	this->tail = NULL;
	this->lenght = 0;

	//Load saved leaderboard
	ifstream fi("leaderboard.bin", ios::binary);
	if (fi.fail()) {
		ofstream fo("leaderboard.bin", ios::binary);
		fo.close();
	}
	else {
		User data;
		while (fi.read((char*)&data, sizeof data)) {
			this->push_back(data);
		}
	}
	fi.close();
}

void LeaderBoard::push_back(User value) {
	UserNode* newNode = new UserNode;

	newNode->data = value;
	newNode->previous = tail;
	newNode->next = NULL;

	if (tail != NULL) {
		tail->next = newNode;
	}

	tail = newNode;

	if (head == NULL) {
		head = newNode;
	}

	this->lenght++;
}

User LeaderBoard::pop_back() {
	if (tail == NULL) {
		cout << "The list is empty" << endl;
		return User();
	}

	UserNode* temp = tail;

	tail = tail->previous;

	if (tail != NULL) {
		tail->next = NULL;
	}

	if (temp == head) {
		head = NULL;
	}

	User data = temp->data;
	delete temp;

	this->lenght--;

	return data;
}

int LeaderBoard::find(User target)
{
	int index = 0;

	UserNode* current = head;
	while (current != NULL) {
		if (current->data == target) return index;
		current = current->next;
		index++;
	}

	return -1;
}

void LeaderBoard::swap(UserNode* a, UserNode* b) {
	User t = a->data;
	a->data = b->data;
	b->data = t;
}

UserNode* LeaderBoard::getNode(int index) {
	if (index >= this->lenght || index < 0) throw "Index out of range";

	UserNode* current = this->head;
	int currentPosition = 0;
	while (current != NULL) {
		if (index == currentPosition) return current;
		current = current->next;
		currentPosition++;
	}
}

User LeaderBoard::at(int index) {
	if (index >= this->lenght || index < 0) throw "Index out of range";

	UserNode* current = this->head;
	int currentPosition = 0;
	while (current != NULL) {
		if (index == currentPosition) return current->data;
		current = current->next;
		currentPosition++;
	}
}

void LeaderBoard::editAt(int index, User data) {
	if (index >= this->lenght || index < 0) throw "Index out of range";

	UserNode* target = getNode(index);
	target->data = data;
}

//Use for debug purpose
void LeaderBoard::printList() {
	UserNode* current = head;
	while (current != NULL) {
		cout << current->data.username << " " << current->data.minute << " " << current->data.second << endl;
		current = current->next;
	}
}

void LeaderBoard::sort() {
	for (int i = 0; i < this->lenght; i++) {
		for (int j = i + 1; j < this->lenght; j++) {
			if (this->getNode(i)->data > this->getNode(j)->data) {
				this->swap(this->getNode(i), this->getNode(j));
			}
		}
	}
}

int LeaderBoard::getSize()
{
	return this->lenght;
}

void LeaderBoard::save() {
	ofstream fo("leaderboard.bin", ios::binary);
	for (int i = 0; i < this->lenght; i++) {
		User data = this->at(i);
		fo.write((char*)&data, sizeof data);
	}
	fo.close();
}

LeaderBoard::~LeaderBoard() {
	//save to leaderboard before exiting
	this->save();

	//Deallocate memory
	while (this->lenght) {
		this->pop_back();
	}
}
