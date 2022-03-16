#pragma once
#include "date.h"
struct Semester {
	int year, term;
	Date startDate, endDate;

	Semester(int year, int term, Date start, Date end) : year(year), term(term), startDate(start), endDate(end) {};
};

