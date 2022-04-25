#include <iostream>
#include "display.h"
#include "user.h"
#include "pvqn.h"
#include "staff.h"
#include "semester.h"
#include "course.h"
#include "schoolYear.h"
#include "student.h"
#include "support.h"

using namespace std;

int main()
{
	Pull();
	User* account = NULL;
	Class* classes = NULL;
	Student* student = NULL;
	Semester* semCur = NULL; //task 6
	Date startSem, endSem;	// task 7
	Course* courseCur = NULL; // task 8
	string username;
	string password;
	int choice;
	int userRole;
	bool logOut = -1;
	do{
		// clear screen
		HANDLE hStdout;
		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		cls(hStdout);
		displaylogin(username, password);
		//clear screen
		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		cls(hStdout);
		// start menu
		userRole = displaymenu(login(username, password, account));
		if (userRole == 1) // student
			logOut = studentChoice(choice, account, username, password, classes, student);
		else if (userRole == 0)// staff
			logOut = staffChoice(choice, account, username, password, classes, student, semCur, courseCur);
		else {
			cout << "WRONG USERNAME OR PASSWORD!" << endl;
			cout << "Please login again!" << endl;
			cout << "Press enter to continue...";
			_getch();
			// clear screen
			HANDLE hStdout;
			hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
			cls(hStdout);
			// start menu
		}
	} while (logOut != 0 && (userRole != 0 || userRole != 1));
	Push();
}
