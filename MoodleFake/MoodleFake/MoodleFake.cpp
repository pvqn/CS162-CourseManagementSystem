#include <iostream>
#include "user.h"
#include "pvqn.h"
#include "staff.h"
#include "semester.h"
#include "course.h"

using namespace std;

int main()
{
	User* account = NULL;
	Class* classes = NULL;
	Semester* semCur = NULL; //task 6
	Date startSem, endSem; int s;// task 7
	Course* courseCur = NULL; // task 8
	string username;
	string password;

	displaylogin(username, password);
	displaymenu(login(username, password, account));
	//viewUserProfile(account);
	//changePass(account);
	staffChoice(account, classes);
	Create_newSemester(semCur);
	CourseRegister(startSem, endSem, s);
	addCourse(courseCur);
	view_Course(courseCur, semCur);
	updateCourse(courseCur);
	DeleteCourse(courseCur);
}
