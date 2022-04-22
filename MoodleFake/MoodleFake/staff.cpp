#include "schoolYear.h"
#include "semester.h"
#include "user.h"
#include "struct.h"
#include "classes.h"
#include "pvqn.h"
#include "student.h"
#include "staff.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include "course.h"
#include "display.h"

void createSchoolYear() {
	int year;
	cout << "Year(yyyy): ";
	cin >> year;
	if (year < 1900 || year > 9000) {
		cout << "Error value";
		return;
	}
	else {
		setCurrentYear(year);
		setCurrentSemester(year, 0, Date(0, 0, 0), Date(0, 0, 0));
		cout << "Year has been created successfully!\n";
		return;
	}
}

void importStudentFromCSV(string className, Student*& student) {
	Student* curStd = student;
	Student* std = NULL;
	int No;
	string id;
	string firstName;
	string lastName;
	string gender;
	Date dob;
	string socialId;

	string path = "csvFile/classes/" + className + ".csv";
	ifstream fin(path);
	string sub; getline(fin, sub);
	while (fin >> No) {
		//Get student info from file .csv
		fin.ignore();
		getline(fin, id, ',');
		getline(fin, firstName, ',');
		getline(fin, lastName, ','); 
		getline(fin, gender, ',');
		fin >> dob.day; fin.ignore();
		fin >> dob.month; fin.ignore();
		fin >> dob.year; fin.ignore();
		getline(fin, socialId, '\n');

		//Add student info to Student Linked List
		std = new Student;
		std->id = id;
		std->firstName = firstName;
		std->lastName = lastName;
		std->gender = gender;
		std->dob.day = dob.day;
		std->dob.month = dob.month;
		std->dob.year = dob.year;
		std->socialId = socialId;
		std->next = NULL;
		if (student == NULL) {
			student = std;
			curStd = student;
		}
		else {
			curStd->next = std;
			curStd = curStd->next;
		}
	}

	fin.close();
}

void addStudent(string className, Student*& student) {
	string year = to_string(getCurrentYear());
	Student* std = student;
	importStudentFromCSV(className, student);

	string path = "data/classes/" + className + "/studentList.txt";
	ofstream fout(path.c_str());
	while (std != NULL) {
		fout << std->id << '\n';
		std = std->next;
	}
	fout.close();
	
	while (student != NULL) {
		//path = "data/Semester/students/";
		//_mkdir(path.c_str());

		path = "data/cache/Semester/students/" + student->id;
		_mkdir(path.c_str());

		path = "data/cache/Semester/students/" + student->id + "/class.txt";
		ofstream fout(path);
		fout << className;
		fout.close();

		path = "data/classes/" + className + "/" + student->id + "_course";
		_mkdir(path.c_str());

		path = "data/classes/" + className + "/studentList.txt";
		fout.open(path, ios::app);
		fout << student->id << "\n";
		fout.close();

		path = "data/classes/" + className + "/" + student->id + ".txt";
		fout.open(path, 'w');
		fout << student->id << "\n";
		fout << student->firstName << "\n";
		fout << student->lastName << "\n";
		fout << student->gender << "\n";
		fout << student->dob.day << "/" << student->dob.month << "/" << student->dob.year << "\n";
		fout << student->socialId;
		fout.close();
		
		student = student->next;
	}

	cout << "Students have been added successfully!\n";
}


void exportCourseStudentListToCSV()
{
	displaycourse_list();
	string Course_name;
	cout << "Please enter course name ( Example CS162 ): "; cin >> Course_name;
	string path = "data/cache/Semester/courseList.txt";
	bool Check = false;

	ifstream fin; ofstream fout;

	fin.open(path);
	while (!fin.eof())
	{
		string cur;
		getline(fin, cur);
		if (cur == Course_name) Check = true;
	}
	fin.close();
	if (!Check)
	{
		cout << "Your finding course is not exist !";
		return;
	}


	string path_in = "data/cache/Semester/coureses/" + Course_name + "/studentList.txt";
	string path_out = "data/cache/csvFile/" + Course_name + ".csv";
	string path_mark = "data/cache/Semester/coureses/" + Course_name + "/mark.txt";
	ifstream Mark; Mark.open(path_mark);
	fin.open(path_in);
	fout.open(path_out);
	fout << "No;ID;Name;Total;Final;Midterm;Other" << '\n';
	int No = 0;
	while (!fin.eof())
	{
		string ID, Name;
		float Mid, Final, Other, Total;
		string ID_mark;
		fin >> ID;
		if (ID.size() == 0) break;
		fin.ignore(); getline(fin, Name);
		//cout << ID << ' ' << Name << endl;
		Mark >> ID_mark >> Total >> Final >> Mid >> Other;
		if (ID != ID_mark)
		{
			system("pause");
			cout << "Error!!!!!!!!!!!!!!!!!!!!!!!!";
		}
		fout << ++No << ';' << ID << ';' << Name << ';' << Total << ';' << Final << ';' << Mid << ';' << Other << '\n';
	}
	fin.close();
	fout.close();
	Mark.close();
}

void ImportCourseScore() // Import + Update
{
	displaycourse_list();
	ifstream fin; ofstream fout;
	string Course_name;
	cout << "Please enter course name ( Example CS162 ): "; cin >> Course_name;
	string path = "data/cache/Semester/coureses/courseList.txt";
	bool Check = false;
	fin.open(path);
	while (!fin.eof())
	{
		string cur; fin >> cur;
		if (cur == Course_name) Check = true;
	}
	fin.close();
	if (!Check)
	{
		cout << "Your finding course is not exist !";
		return;
	}

	string path_in = "data/cache/csvFile/" + Course_name + "_teacher.csv";
	string path_out = "data/cache/csvFile/" + Course_name + ".csv";
	fin.open(path_in); fout.open(path_out);
	while (!fin.eof())
	{
		string current;
		getline(fin, current);
		fout << current << '\n';
	}
	fin.close(); fout.close();

	// Update mark.txt in course
	path_in = "data/cache/csvFile/" + Course_name + ".csv";
	path_out = "data/cache/Semester/coureses/" + Course_name + "/mark.txt";
	fin.open(path_in); fout.open(path_out);
	string Delete;
	getline(fin, Delete);
	while (!fin.eof())
	{
		string current;
		getline(fin, current);
		int count = 0;
		for (int i = 0; i < current.size(); ++i)
		{
			if (current[i] == ';')
			{
				++count;
				if (count == 2 || count == 4 || count == 5 || count == 6 ) fout << '\n';
				continue;
			}
			if (count == 1 || count == 3 || count == 4 || count == 5 || count == 6) fout << current[i];
		}
		fout << '\n';
	}
	fin.close(); fout.close();

	// Update mark.txt in students folder
	path_in = "data/cache/Semester/coureses/" + Course_name + "/mark.txt";

	fin.open(path_in);
	while (!fin.eof())
	{
		string ID, Total, Mid, Final, Other;
		fin >> ID >> Total >> Final >> Mid >> Other;
		if (ID.size() == 0) break;
		path_out = "data/cache/Semester/students/" + ID + "/" + Course_name + "_mark.txt";
		//cout << path_out << endl;
		fout.open(path_out);
		fout << Total << '\n' << Final << '\n' << Mid << '\n' << Other << '\n';
		fout.close();
	}
	fin.close();

	// Update mark in classes
	path_in = "data/cache/Semester/coureses/" + Course_name + "/mark.txt";
	fin.open(path_in);
	while (!fin.eof())
	{
		string ID, Total, Mid, Final, Other, classID;
		fin >> ID >> Total >> Final >> Mid >> Other;
		// Find class
		ifstream FindClass;
		string path_class = "data/cache/Semester/students/" + ID + "/class.txt";
		FindClass.open(path_class);
		FindClass >> classID;
		FindClass.close();
		// Update mark
		path_out = "data/classes/" + classID + "/" + ID + "_course/" + Course_name + "_mark.txt";
		fout.open(path_out);
		fout << Total << '\n' << Final << '\n' << Mid << '\n' << Other << '\n';
		fout.close();
	}
	fin.close();
}

bool staffChoice(int& choice, User*& account, string& username, string& password, Class*& classes, Student* student, Semester* semCur,Course*& courseCur) {
	string className;
	do {
		cout << "\nInput your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1: //View info
			viewUserProfile(account);
			break;
		case 2: //Change password
			changePass(account);
			break;
		case 3: //Create a school year
			createSchoolYear();
			break;
		case 4: //Create a class
			createClass(classes);
			break;
		case 5: //Add new student
			cout << "Input class name: ";
			cin >> className;
			addStudent(className, student);
			break;
		case 6: //Create a semester
			Create_newSemester(semCur);
			//cout << semCur->year << " " << semCur->term << endl;
			break;
		case 7: //Create a course registration
			CourseRegister( semCur->term, semCur->year);
			break;
		case 8: //Add a course to semester
			addCourse(courseCur);
			break;
		case 9: //View the list of courses in the semester
			cout << "The list of courses in the semester: ";
			view_Course(courseCur);
			break;
		case 10: //Update course information
			updateCourse(courseCur);
			break;
		case 11: //Delete a course
			DeleteCourse(courseCur,semCur);
			break;
		case 12: //View a list of classes
			viewclass();
			break;
		case 13: //View a list of students in a class
			displayclass_student();
			break;
		case 14: //View a list of courses in the system
			displaycourse_list();
			break;
		case 15: //View a list of students in a course
			displaycourse_studentList();
			break;
		case 16: //Export a list of students in a course to a csv file
			exportCourseStudentListToCSV();
			break;
		case 17: //Import the scoreboard of a course
			ImportCourseScore();
			break;
		case 18: //View the scoreboard of a course
			viewScoreboardOfCourse();
			break;
		case 19: //View the scoreboard of a class
			viewScoreinClass();
			break;
		case 20: //Log out
			return 1;
		default:
			break;
		}
		cout << endl;
		cout << "\npress enter to continue...";
		_getch();
		HANDLE hStdout;
		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		cls(hStdout);

		displaymenu(0);
	} while (choice != 21);
	return 0;
}

void viewScoreboardOfCourse() // In bang diem mon hoc
{
	displaycourse_list();
	ifstream fin; ofstream fout;
	string Course_name;
	cout << "Please enter course name ( Example CS162 ): "; cin >> Course_name;
	string path = "data/cache/Semester/coureses/courseList.txt";
	bool Check = false;
	fin.open(path);
	while (!fin.eof())
	{
		string cur; fin >> cur;
		if (cur == Course_name) Check = true;
	}
	fin.close();
	if (!Check)
	{
		cout << "Your finding course is not exist !";
		return;
	}

	string path_in = "data/cache/csvFile/" + Course_name + ".csv";
	fin.open(path_in);

	cout << setw(3) << left << "No"; cout << '|';
	cout << setw(12) << left << "Student ID"; cout << '|';
	cout << setw(30) << right << "Full name"; cout << '|';
	cout << setw(6) << right << "Total"; cout << '|';
	cout << setw(6) << right << "Fianl"; cout << '|';
	cout << setw(6) << right << "Mid"; cout << '|';
	cout << setw(6) << right << "Other"; cout << '\n';
	cout << setfill('-');		// set fill bang ky tu '-' thay vi ' '
	cout << setw(75) << "-" << endl;	// fill 75 ky tu '-'
	cout << setfill(' ');
	string Delete;
	getline(fin, Delete);
	while (!fin.eof())
	{
		string current;
		getline(fin, current);
		if (current.size() == 0) break;
		string List[7]; // No, ID, Full name, Total, Final, Mid, Other
		int cnt = 0;
		for (int i = 0; i < current.size(); ++i)
		{
			if (current[i] == ';')
			{
				++cnt;
				continue;
			}
			List[cnt] += current[i];
		}
		cout << setw(3) << left << List[0]; cout << '|';
		cout << setw(12) << left << List[1]; cout << '|';
		cout << setw(30) << right << List[2]; cout << '|';
		cout << setw(6) << right << List[3]; cout << '|';
		cout << setw(6) << right << List[4]; cout << '|';
		cout << setw(6) << right << List[5]; cout << '|';
		cout << setw(6) << right << List[6]; cout << '\n';
	}

	fin.close();
}

void viewScoreinClass()
{
	viewclass();
	string classname;
	cout << "Please enter the class: "; cin >> classname;
	ifstream fin; ofstream out;

	// Check the class is exist or not
	string path_in = "data/classes/classList.txt";
	fin.open(path_in);
	bool check = false;
	while (!fin.eof())
	{
		string current;
		getline(fin, current);
		if (classname == current) check = true;
	}
	fin.close();
	if (!check)
	{
		cout << "This class is not exist !";
		return;
	}

	// Print score board
	cout << setw(3) << left << "No"; cout << '|';
	cout << setw(12) << left << "Student ID"; cout << '|';
	cout << setw(30) << right << "Full name"; cout << '|';
	path_in = "data/cache/Semester/courseList.txt";
	fin.open(path_in);
	int course_cnt = 0;
	while (!fin.eof())
	{
		string course_name;
		getline(fin, course_name);
		if (course_name.size() == 0) break;
		cout << setw(10) << right << course_name; cout << '|';
		++course_cnt;
		getline(fin, course_name);
	}
	fin.close();
	cout << setw(5) << right << "GPA"; cout << '|' << '\n';
	cout << setfill('-');		// set fill bang ky tu '-' thay vi ' '
	cout << setw(54 + (course_cnt * 11) ) << "-" << endl;	// fill ky tu '-'
	cout << setfill(' ');

	int No = 0; float total_GPA = 0;
	string path_student = "data/classes/" + classname + "/studentList.txt";
	fin.open(path_student);
	while (!fin.eof())
	{
		string studentID;
		getline(fin, studentID);
		if (studentID.size() == 0) break;
		//cout << studentID << endl;
		// Print student info
		cout << setw(3) << left << ++No; cout << '|';
		cout << setw(12) << left << studentID; cout << '|';
		ifstream fin_name;
		string path_name = "data/classes/" + classname + "/" + studentID + ".txt";
		fin_name.open(path_name);
		string First, Last;
		getline(fin_name, First); getline(fin_name, First);
		getline(fin_name, Last);
		First = Last + ' ' + First;
		cout << setw(30) << right << First; cout << '|';
		fin_name.close();

		// Print score board
		ifstream fin_course; int total_credit = 0; float total_score = 0;
		fin_course.open("data/cache/Semester/courseList.txt");

		while (!fin_course.eof())
		{
			string course_name; float Total; int credit;
			getline(fin_course, course_name);
			if (course_name.size() == 0) break;
			//cout << course_name << endl;
			string path_mark = "data/classes/" + classname + "/" + studentID + "_course/" + course_name + "_mark.txt";
			ifstream fin_mark;
			fin_mark.open(path_mark);
			if (fin_mark.fail())
			{
				cout << setw(10) << "N/A"; cout << '|';
				getline(fin_course, course_name);
				continue;
			}
			fin_mark >> Total;
			fin_mark.close();
			cout << setw(10) << Total; cout << '|';

			string path_credit = "data/cache/Semester/coureses/" + course_name + "/info_Of_Course.txt";
			ifstream fin_credit;
			fin_credit.open(path_credit);
			string current; getline(fin_credit, current);
			fin_credit >> credit;
			fin_credit.close();
			total_credit += credit;
			if (0 <= Total && Total <= 3.9) total_score += 0;
			if (4.0 <= Total && Total <= 5.4) total_score += 1 * credit;
			if (5.5 <= Total && Total <= 6.9) total_score += 2 * credit;
			if (7.0 <= Total && Total <= 8.4) total_score += 3 * credit;
			if (8.0 <= Total && Total <= 10 ) total_score += 4 * credit;
			getline(fin_course, course_name);
		}

		fin_course.close();
		cout << setw(5) << right << total_score / total_credit; cout << '|' << '\n';
		total_GPA += total_score / total_credit;
		//cout << '\n';
	}
	fin.close();

	total_GPA /= No;
	cout << setfill('-');		// set fill bang ky tu '-' thay vi ' '
	cout << setw(54 + (course_cnt * 11)) << "-" << endl;	// fill ky tu '-'
	cout << setfill(' ');
	cout << setw(49 + (course_cnt * 11)) << right << "Averange GPA"; cout << '|';
	cout << setw(3) << fixed << setprecision(2) << right << total_GPA; cout << '|';
}

void displayclass_student() // display class students
{
	viewclass();
	string Classname;
	cout << "Enter class name: "; cin >> Classname;
	// Find class is exit or not
	string path = "data/classes/classList.txt";
	ifstream fin(path);
	bool Find = false;
	while (!fin.eof())
	{
		string Name;
		fin >> Name;
		if (Name == Classname)
		{
			Find = true;
			break;
		}
	}
	fin.close();
	// The case: class is not exist
	if (!Find)
	{
		cout << "This class is not exist !";
		return;
	}

	// Create student list ID
	path = "data/classes/" + Classname + "/studentList.txt";
	fin.open(path);

	int Number_of_student = 0;
	int* studentList = new int[1000];
	int studentID;
	while (fin >> studentID)
	{
		studentList[Number_of_student++] = studentID;
	}
	
	fin.close();
	// Display student information
	int No = 0;
	for (int i = 0; i < Number_of_student; ++i)
	{
		path = "data/classes/" + Classname + '/' + to_string(studentList[i]) + ".txt";

		
		string ID, First_name, Last_name, socialID;
		bool Gender;
		Date DOB;

		fin.open(path);
		fin >> ID;
		fin.ignore(); getline(fin, First_name);
		getline(fin, Last_name);
		// fin >> Gender;
		// fin >> DOB.day >> DOB.month >> DOB.year;
		// fin >> socialID;

		cout << ++No << ' ' << ID << ' ' << Last_name << ' ' << First_name << '\n';

		fin.close();
	}
	delete[] studentList;
}

void displaycourse_list() // In ra danh sach cac khoa hoc
{
	cout << "This is the course list: " << '\n';
	// Print the course list of this semester
	string path = "data/cache/Semester/coureses/courseList.txt";
	ifstream fin;
	fin.open(path);
	while (!fin.eof())
	{
		string cur;
		getline(fin, cur);
		cout << cur << '\n';
	}
	fin.close();
}

void displaycourse_studentList()
{
	displaycourse_list();
	// Print student in this course
	string Course_name;
	cout << "Please enter course name ( Example CS162 ): "; cin >> Course_name;
	string path = "data/cache/Semester/coureses/courseList.txt";
	bool Check = false;
	ifstream fin;
	fin.open(path);
	while (!fin.eof())
	{
		string cur; fin >> cur;
		if (cur == Course_name) Check = true;
	}
	fin.close();
	if (!Check)
	{
		cout << "Your finding course is not exist !";
		return;
	}

	path = "data/cache/Semester/coureses/" + Course_name + "/studentList.txt";
	fin.open(path);
	int No = 0;
	while (!fin.eof())
	{
		string ID, Name;
		fin >> ID;
		fin.ignore(); getline(fin, Name);
		cout << ++No << ' ' << ID << ' ' << Name << '\n';
	}
	fin.close();
}
