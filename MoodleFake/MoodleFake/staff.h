#pragma once
#include "struct.h"

using namespace std;

void staffChoice(User* acc, Class*& classes);
void createSchoolYear();
void importStudentFromCSV(string className, string courseID, Student*& student);
void ImportCourseScore();
void ExportCourseStudentList();
void viewScoreboardOfCourse();
void viewScoreinClass();

