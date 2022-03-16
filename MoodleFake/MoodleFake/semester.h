#pragma once
#include <string>
#include <direct.h>
#include <fstream>
#include "date.h"

using namespace std;

struct Semester {
	int year, term;
	Date* startDate,* endDate;
};

void setCurrentSemester(int year, int term, Date start, Date end);


