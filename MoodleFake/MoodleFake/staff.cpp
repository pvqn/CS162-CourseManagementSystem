#include "schoolYear.h"
#include "semester.h"
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

void addStudentFromCSV(string className,string courseID, Student*& student) {
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
		std->courseID = courseID;
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
