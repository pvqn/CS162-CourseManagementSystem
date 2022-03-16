#pragma once
#include <string>
#include <iostream>

using namespace std;

struct User {
	string username;
	string password;
	string role;
	string Class;

	User(string username, string password, string role, string Class) :
		username(username), password(password), role(role), Class(Class) {};
	User() {};
};

