#pragma once
#include "struct.h"

using namespace std;

void staffChoice(User* acc, Class*& classes, Student*& student);
void createSchoolYear();
void importStudentFromCSV(string className, Student*& student);
void addStudent(string className, Student*& student);
void ImportCourseScore();
void ExportCourseStudentList();
void viewScoreboardOfCourse();
void viewScoreinClass();

