#include <iostream>
#include "user.h"
#include "pvqn.h"
#include "staff.h"
#include "semester.h"
#include "course.h"
#include "schoolYear.h"
#include "student.h"

using namespace std;

int main()
{
	User* account = NULL;
	Class* classes = NULL;
	Student* student = NULL;
	Semester* semCur = NULL; //task 6
	Date startSem, endSem;	// task 7
	Course* courseCur = NULL; // task 8
	string username;
	string password;
	int choice;
	bool logOut = -1;
	do{
		displaylogin(username, password);
		if (displaymenu(login(username, password, account)))
			logOut = studentChoice(choice, account, username, password, classes, student); // student
		else // staff
			logOut = staffChoice(choice, account, username, password, classes, student,semCur,courseCur);
	} while (logOut != 0);
	//Create_newSemester(semCur);
	//CourseRegister(startSem, endSem, semCur->term, semCur->year);
	//addCourse(courseCur);
	//view_Course(courseCur, semCur);
	//updateCourse(courseCur);
	//DeleteCourse(courseCur);
}
