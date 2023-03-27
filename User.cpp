#include "User.h"
#include <iostream>

UserList::UserList() {
	this->head = NULL;
	this->tail = NULL;
	this->lenght = 0;
}

void UserList::push_back(User)
{
}

User UserList::pop_back()
{
	return User();
}

int UserList::find(User)
{
	return 0;
}

User UserList::at(int)
{
	return User();
}

UserList::~UserList() {
	while (this->lenght) {
		this->pop_back();
	}
}
