#pragma once
struct User {
	char username[32];
	int score;
};

struct UserNode{
	User data;
	UserNode* next;
	UserNode* previous;
};

class UserList{
private:
	int lenght;
	UserNode* head;
	UserNode* tail;
public:
	UserList();
	void push_back(User);
	User pop_back();
	int find(User);
	User at(int);
	~UserList();
};

