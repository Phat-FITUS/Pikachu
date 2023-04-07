#pragma once
#include <cstring>

struct User {
	char username[32];
	int minute, second;
	int mode;

	void operator = (User other) {
		strcpy(this->username, other.username);
		this->minute = other.minute;
		this->second = other.second;
		this->mode = other.mode;
	}

	bool operator == (User other) {
		return (strcmp(this->username, other.username) == 0) && (this->mode == other.mode);
	}

	bool operator > (User other) {
		return (this->minute * 60 + this->second) > (other.minute * 60 + other.second);
	}

	User() {
		this->username[0] = 0;
		this->minute = 60;
		this->second = 60;
		this->mode = 0;
	}

	User(const char* username, int minute, int second, int mode) {
		strcpy(this->username, username);
		this->minute = minute;
		this->second = second;
		this->mode = mode;
	}
};

struct UserNode {
	User data;
	UserNode* next;
	UserNode* previous;
};

class LeaderBoard {
private:
	int lenght;
	UserNode* head;
	UserNode* tail;
	UserNode* getNode(int);
	void swap(UserNode*, UserNode*);
public:
	LeaderBoard();
	void push_back(User);
	User pop_back();
	int find(User);
	User at(int);
	void editAt(int, User);
	void printList();
	void sort();
	int getSize();
	void save();
	~LeaderBoard();
};

