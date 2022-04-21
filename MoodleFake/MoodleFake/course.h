#pragma once
#include "struct.h"

using namespace std;


void addCourse(Course*& pCourse, Semester* s);
void view_Course(Course* pCur, Semester* Scur);
void updateCourse(Course*& pCur, Semester* s);

void DeleteCourse(Course*& pCourse);
Course* add();

