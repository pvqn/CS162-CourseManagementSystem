#pragma once
#include "struct.h"



void setCurrentSemester(int year, int term, Date start, Date end);
Semester getCurrentSemester();
void Create_newSemester(Semester*& Scur);
void CourseRegister(int semester, int year);


