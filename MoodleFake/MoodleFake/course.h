#pragma once
#include "struct.h"

using namespace std;


void addCourse(Course* pCourse, Course* newCourse);
void view_Course(Course* pCur, Semester* Scur);
void updateCourse(Course* pCur, string id);

void DeleteCourse(Course* pCourse, string id);

