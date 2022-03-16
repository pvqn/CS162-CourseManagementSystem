#pragma once
#include <iostream>
#include <string>

#include "Date.h"

using namespace std;

struct Student {
	string id;
	string firstName;
	string lastName;
	bool gender;
	Date dob; // date of birth
	string socialId;
	string courseID;

	Student(string id, string firstName, string lastName, bool gender, Date dob, string socialId, string courseID) :
		id(id), firstName(firstName), lastName(lastName), gender(gender), dob(dob), socialId(socialId), courseID(courseID) {};
	Student() {};
};

