#include <iostream>
#include "user.h"
#include "pvqn.h"
#include <iostream>
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
	Date startSem, endSem; int s;// task 7
	Course* courseCur = NULL; // task 8
	string username;
	string password;
	int choice = 0;

	displaylogin(username, password);
	if (displaymenu(login(username, password, account)))
		studentChoice(choice, account, username, password, classes, student); // student
	else // staff
		staffChoice(choice, account, username, password, classes, student);

	//Create_newSemester(semCur);
	//CourseRegister(startSem, endSem, s);
	//addCourse(courseCur);
	//view_Course(courseCur, semCur);
	//updateCourse(courseCur);
	//DeleteCourse(courseCur);
}
