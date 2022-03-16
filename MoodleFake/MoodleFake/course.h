#pragma once
#include <string>
#include <iostream>

#include "mark.h"


using namespace std;

struct Course {
	string id;
	string name;
	string teacher;
	int nCredits;
	int maxCapacity;
	string day1, ses1;
	string day2, ses2;

	Course(string id, string name, string teacher, int nCredits, int maxCapacity, string day1, string ses1, string day2, string ses2) :
		id(id), name(name), teacher(teacher), nCredits(nCredits), maxCapacity(maxCapacity), day1(day1), ses1(ses1), day2(day2), ses2(ses2)
	{};
	Course() {};
};

//Không cần tạo student list vì muốn search student trong 1 course thì dùng function search, chứ tạo nữa rối :v


