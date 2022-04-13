#pragma once
#include "struct.h"

using namespace std;

bool staffChoice(int& choice, User*& account, string& username, string& password, Class*& classes, Student* student, Semester* semCur, Course* courseCur);
void createSchoolYear();
void importStudentFromCSV(string className, Student*& student);
void addStudent(string className, Student*& student);
void ImportCourseScore();
void exportCourseStudentListToCSV();
void viewScoreboardOfCourse();
void viewScoreinClass();

void displayclass_student(); // display class students
void displaycourse_list(); // In ra danh sach cac khoa hoc
void displaycourse_studentList();
