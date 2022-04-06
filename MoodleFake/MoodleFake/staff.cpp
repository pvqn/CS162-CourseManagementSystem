#include "schoolYear.h"
#include "semester.h"
#include "user.h"
#include "struct.h"
#include "classes.h"


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
	Student* curStd = NULL;
	Student* std = NULL;
	int No;
	string id;
	string firstName;
	string lastName;
	bool gender;
	Date dob;
	string socialId;

	string path = "csvFile/classes/" + className + ".csv";
	ifstream fin(path);
	while (!fin.eof()) {
		//Get student info from file .csv
		getline(fin, id, ',');
		getline(fin, firstName, ',');
		getline(fin, lastName, ',');
		fin >> gender; fin.ignore();
		fin >> dob.day; fin.ignore();
		fin >> dob.month; fin.ignore();
		fin >> dob.year; fin.ignore();
		getline(fin, socialId, '\n');

		//Add student info to Student Linked List
		std = new Student;
		curStd = new Student;
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
			curStd = std;
		}
	}
	fin.close();
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

void staffChoice(User* acc, Class*& classes) {
	int choice;
	cout << "Input your choice: ";
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
		//importStudentFromCSV();
		break;
	default:
		break;
	}
}