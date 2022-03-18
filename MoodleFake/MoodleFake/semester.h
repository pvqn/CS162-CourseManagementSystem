#pragma once
#include <string>
#include <direct.h>
#include <fstream>
#include "date.h"
#include "course.h"
using namespace std;

struct Semester {
	int year, term;
	Date startDate, endDate;
	// doi date * thanh date
	Course* course_cur = nullptr;
	Semester* next = nullptr;
	
};

void setCurrentSemester(int year, int term, Date start, Date end);


