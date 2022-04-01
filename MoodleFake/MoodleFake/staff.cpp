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

void ImportCourseScore()
{
	//  Enter the year and the semester
	int Year = 0, Term = 0;
	cout << "Please input the year: "; cin >> Year;
	cout << "Please input the semester: "; cin >> Term;

	// Print student in this course
	ifstream fin; ofstream fout;
	string Course_name;

	cout << "Please enter course name ( Example CS162 ): "; cin >> Course_name;
	string path = "data/" + to_string(Year) + '/' + to_string(Term) + "/courseList.txt";
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

	string path_in = "data/" + to_string(Year) + '/' + to_string(Term) + "/" + Course_name + "/Teacher.csv";
	string path_out = "data/" + to_string(Year) + '/' + to_string(Term) + "/" + Course_name + "/StudentList.csv";
	fin.open(path_in); fout.open(path_out);
	while (!fin.eof())
	{
		string current;
		getline(fin, current);
		fout << current << '\n';
	}
	fin.close(); fout.close();

	path_in = "data/" + to_string(Year) + '/' + to_string(Term) + "/" + Course_name + "/StudentList.csv";
	path_in = "data/" + to_string(Year) + '/' + to_string(Term) + "/" + Course_name + "/mark.txt";
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
}