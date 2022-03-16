#pragma once
#include <iostream>
#include <string>

#include "Date.h"

using namespace std;

struct Student {
	Student* next;
	string id;
	string firstName;
	string lastName;
	bool gender;
	Date* dob; // date of birth
	string socialId;
	string courseID;
};

