#include "schoolYear.h"
#include "semester.h"
#include "user.h"
#include "struct.h"
#include "classes.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>


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
		cout << "Year has been created successfully";
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
		path = "data/" + year + "/1/students/" + student->id;
		_mkdir(path.c_str());

		path = "data/" + year + "/1/students/" + student->id + "/" + className + ".txt";
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
}


void ExportCourseStudentList()
{
	//  Enter the year and the semester
	int Year = 0, Term = 0;
	cout << "Please input the year: "; cin >> Year;
	cout << "Please input the semester: "; cin >> Term;

	// Print student in this course
	string Course_name;
	cout << "Please enter course name ( Example CS162 ): "; cin >> Course_name;
	string path = "data/" + to_string(Year) + '/' + to_string(Term) + "/courseList.txt";
	bool Check = false;

	ifstream fin;
	ofstream fout;

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

	string path_in = "data/" + to_string(Year) + '/' + to_string(Term) + "/" + Course_name + "/studentList.txt";
	string path_out = "data/" + to_string(Year) + '/' + to_string(Term) + "/" + Course_name + "/StudentList.csv";
	string path_mark = "data/" + to_string(Year) + '/' + to_string(Term) + "/" + Course_name + "/mark.txt";
	ifstream Mark; Mark.open(path_mark);
	fin.open(path_in);
	fout.open(path_out);
	fout << "No,ID,Name,Midterm Mark,Final mark,Other mark,Total mark" << '\n';
	int No = 0;
	while (!fin.eof())
	{
		string ID, Name;
		float Mid, Final, Other, Total;
		string ID_mark;

		fin >> ID;
		fin.ignore(); getline(fin, Name);
		Mark >> ID_mark >> Mid >> Final >> Other >> Total;
		if (ID != ID_mark)
		{
			system("pause");
			cout << "Error!!!!!!!!!!!!!!!!!!!!!!!!";
		}
		fout << ++No << ',' << ID << ',' << Name << ',' << Mid << ',' << Final << ',' << Other << ',' << Total << '\n';
	}
	fin.close();
	fout.close();
	Mark.close();
}

void ImportCourseScore() // Import + Update
{
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
	while (!fin.eof())
	{
		string current;
		getline(fin, current);
		int count = 0;
		for (int i = 0; i < current.size(); ++i)
		{
			if (current[i] == ',')
			{
				++count;
				if (count == 2 || count == 4 || count == 5 || count == 6 ) fout << '\n';
				continue;
			}
			if (count == 1 || count == 3 || count == 4 || count == 5 || count == 6) fout << current[i];
		}
		fout << '\n';
	}
	fin.open(path_in); fout.open(path_out);

	// Update mark.txt in students folder
	path_in = "data/cache/Semester/coureses/" + Course_name + "/mark.txt";

	fin.open(path_in);
	while (!fin.eof())
	{
		string ID, Total, Mid, Final, Other;
		fin >> ID >> Total >> Mid >> Final >> Other;
		path_out = "data/cache/Semester/students/" + ID + "/" + Course_name + "/_mark.txt";
		fout.open(path_out);
		fout << Total << '\n' << Mid << '\n' << Final << '\n' << Other << '\n';
		fout.close();
	}
	fin.close();

	// Update mark in classes
	path_in = "data/cache/Semester/coureses/" + Course_name + "/mark.txt";
	fin.open(path_in);
	while (!fin.eof())
	{
		string ID, Total, Mid, Final, Other, classID;
		fin >> ID >> Total >> Mid >> Final >> Other;
		// Find class
		ifstream FindClass;
		string path_class = "data/cache/Semester/students/" + ID + "/class.txt";
		FindClass.open(path_class);
		FindClass >> classID;
		FindClass.close();
		// Update mark
		path_out = "data/classes/" + classID + "/" + ID + "_course/" + Course_name + "_mark.txt";
		fout.open(path_out);
		fout << Total << '\n' << Mid << '\n' << Final << '\n' << Other << '\n';
		fout.close();
	}
	fin.close();

	// Not yet !!!!!!!!!!!!!!!!!
}

void staffChoice(User* acc, Class*& classes, Student*& student) {
	int choice = 0;
	string className;
	do {
		cout << "\nInput your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			viewUserProfile(acc);
			break;
		case 2:
			changePass(acc);
			break;
		case 3:
			createSchoolYear();
			break;
		case 4:
			createClass(classes);
			break;
		case 5:
			cout << "Input class name: ";
			cin >> className;
			addStudent(className, student);
			break;
		default:
			break;
		}
	} while (choice != 21);
}

void viewScoreboardOfCourse() // In bang diem mon hoc
{
	system("clrscr");
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
	cout << setw(6) << right << "Mid"; cout << '|';
	cout << setw(6) << right << "Final"; cout << '|';
	cout << setw(6) << right << "Other"; cout << '\n';
	cout << setfill('-');		// set fill bang ky tu '-' thay vi ' '
	cout << setw(75) << "-" << endl;	// fill 75 ky tu '-'
	cout << setfill(' ');
	while (!fin.eof())
	{
		string current;
		getline(fin, current);
		if (current.size() == 0) break;
		string List[7]; // No, ID, Full name, Total, Mid, Final, Other
		int cnt = 0;
		for (int i = 0; i < current.size(); ++i)
		{
			if (current[i] == ',')
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
	cout << setw(5) << right << "GPA"; cout << '|';
	cout << setfill('-');		// set fill bang ky tu '-' thay vi ' '
	cout << setw(54 + (course_cnt * 11) ) << "-" << endl;	// fill ky tu '-'
	cout << setfill(' ');

	int No = 0; float total_GPA = 0;
	string path_student = "data/classes/" + classname + "/classList.txt";
	fin.open(path_student);
	while (!fin.eof())
	{
		string studentID;
		getline(fin, studentID);
		if (studentID.size() == 0) break;

		// Print student info
		cout << setw(3) << left << ++No; cout << '|';
		cout << setw(12) << left << studentID; cout << '|';
		ifstream fin_name;
		string path_name = "data/classes/" + classname + "/" + studentID + ".txt";
		fin_name.open(path_name);
		string First, Last;
		getline(fin_name, First); getline(fin_name, First);
		getline(fin_name, Last);
		First += " " + Last;
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

			string path_mark = "data/classes/" + classname + "/" + studentID + "_course/" + course_name + "_mark.txt";
			ifstream fin_mark;
			fin_mark.open(path_mark);
			if (fin_mark.fail())
			{
				cout << setw(10) << "N/A"; cout << '|';
				continue;
			}
			fin_mark >> Total;
			fin_mark.close();
			cout << setw(10) << Total; cout << '|';

			string path_credit = "data/cache/Semester/courses/" + course_name + "/info_Of_Course.txt";
			ifstream fin_credit;
			fin_credit.open(path_credit);
			string current; for (int i = 0; i < 3; ++i) getline(fin_credit, current);
			fin_credit >> credit;
			fin_credit.close();
			total_credit += credit;
			if (0 <= Total && Total <= 3.9) total_score += 0;
			if (4.0 <= Total && Total <= 5.4) total_score += 1 * credit;
			if (5.5 <= Total && Total <= 6.9) total_score += 2 * credit;
			if (7.0 <= Total && Total <= 8.4) total_score += 3 * credit;
			if (8.0 <= Total && Total <= 10 ) total_score += 4 * credit;
		}

		fin_course.close();
		cout << setw(5) << right << total_score / total_credit; cout << '|';
		total_GPA += total_score / total_credit;
		cout << '\n';
	}
	fin.close();

	total_GPA /= No;
	cout << setfill('-');		// set fill bang ky tu '-' thay vi ' '
	cout << setw(54 + (course_cnt * 11)) << "-" << endl;	// fill ky tu '-'
	cout << setfill(' ');
	cout << setw(49 + (course_cnt * 11)) << right << "Averange GPA"; cout << '|';
	cout << setw(3) << fixed << setprecision(2) << right << total_GPA; cout << '|';
}