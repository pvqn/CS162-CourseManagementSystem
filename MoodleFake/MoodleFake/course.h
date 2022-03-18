#pragma once
#include <string>
#include <iostream>

#include "mark.h"

using namespace std;

struct student_list
{
	string id;
	Mark mark;
	student_list* next = nullptr;
};
struct Course 
{
	string id;
	string name;
	string teacher;
	int nCredits;
	int maxCapacity;
	string day1, ses1;
	string day2, ses2;
	student_list* student = nullptr;
	Course* next = nullptr;
};

//Không cần tạo student list vì muốn search student trong 1 course thì dùng function search, chứ tạo nữa rối :v


