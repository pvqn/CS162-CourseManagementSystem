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

void getStudentFromCSV(string courseID, Student*& student) {
	Student* std = NULL;
	int No;
	string id;
	string firstName;
	string lastName;
	bool gender;
	Date dob;
	string socialId;

	string path = "csvFile/course/" + courseID + ".csv";
	ifstream fin(path);
	while (!fin.eof()) {
		getline(fin, id, ',');
		getline(fin, firstName, ',');
		getline(fin, lastName, ',');
		fin >> gender; fin.ignore();
		fin >> dob.day; fin.ignore();
		fin >> dob.month; fin.ignore();
		fin >> dob.year; fin.ignore();
		getline(fin, socialId, '\n');

		student->id = id;
		student->firstName = firstName;
		student->lastName = lastName;
		student->gender = gender;
		student->dob.day = dob.day;
		student->dob.month = dob.month;
		student->dob.year = dob.year;
		student->socialId = socialId;
		student->courseID = courseID;

		student = student->next;
	}
	fin.close();
}

void addStudentFromCSV(string classID) {
	//Dang lam :))
}