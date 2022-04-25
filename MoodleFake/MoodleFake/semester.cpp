#include "struct.h"
#include "support.h"

void setCurrentSemester(int year, int term, Date start, Date end) {
	string path = "data/" + to_string(year) + '/' + to_string(term) + "/info_Of_Semester.txt";
	ofstream fout(path);

	fout << year << endl;
	fout << term << endl;
	fout << start.day << ' ';
	fout << start.month << ' ';
	fout << start.year << endl;
	fout << end.day << ' ';
	fout << end.month << ' ';
	fout << end.year << endl;

	fout.close();
	path = "data/cache/currentSemester.txt";
	fout.open(path);
	fout << year << endl;
	fout << term << endl;

	fout << start.day << ' ';
	fout << start.month << ' ';
	fout << start.year << ' ' << endl;

	fout << end.day << ' ';
	fout << end.month << ' ';
	fout << end.year << endl;
	fout.close();

	path = "data/" + to_string(year) + '/' + to_string(term);
	_mkdir(path.c_str());
	path = "data/" + to_string(year) + '/' + to_string(term) + "/courses";
	_mkdir(path.c_str());
	path = "data/" + to_string(year) + '/' + to_string(term) + "/students";
	_mkdir(path.c_str());


	path = "csvFile/" + to_string(year) + '/' + to_string(term);
	_mkdir(path.c_str());
}

Semester getCurrentSemester() { //Lấy thông tin của Semester hiện tại
	Semester currentSemester;
	int year;
	int term;
	int startday, startmonth, startyear;
	int endday, endmonth, endyear;

	ifstream fin("data/cache/currentSemester.txt");
	fin >> year;
	fin >> term;
	fin >> startday >> startmonth >> startyear;
	fin >> endday >> endmonth >> endyear;
	fin.close();

	currentSemester.year = year;
	currentSemester.term = term;
	currentSemester.startDate = Date(startday, startmonth, startyear);
	currentSemester.endDate = Date(endday, endmonth, endyear);

	return currentSemester;
	//>>>>>>> 4721181f85f83214196216fde0364355879f3ba6
}
void Create_newSemester(Semester*& Scur)
{
	Push();
	reset_cache();
	Semester* s = new Semester;

	cout << "Input Year: "; cin >> s->year;
	cout << "Input Term: "; cin >> s->term;
	cout << "Start Day: "; cin >> s->startDate.day >> s->startDate.month >> s->startDate.year;
	cout << "End Day: "; cin >> s->endDate.day >> s->endDate.month >> s->endDate.year;
	//s->Course

	Scur = s; /// Since we just need to create one semester
	// FROM
	string PATH = "data/" + to_string(s->year);
	_mkdir(PATH.c_str());

	PATH = "data/" + to_string(s->year) + "/" + to_string(s->term);
	_mkdir(PATH.c_str());

	PATH = "data/" + to_string(s->year) + "/" + to_string(s->term) + "/coureses";
	_mkdir(PATH.c_str());

	//TO
	//FROM

	PATH = "csvFile/" + to_string(s->year);
	_mkdir(PATH.c_str());

	PATH = "csvFile/" + to_string(s->year) + "/" + to_string(s->term);
	_mkdir(PATH.c_str());

	//TO

	//FROM
	PATH = "data/" + to_string(s->year) + "/" + to_string(s->term) + "/students";
	_mkdir(PATH.c_str());
	PATH = "data/classes/classList.txt";
	ifstream fin; fin.open(PATH, ios::in);
	while (!fin.eof())
	{
		string sss;
		getline(fin, sss);
		if (sss.size() == 0) break;
		string PATH_PATH = "data/classes/" + sss + "/studentList.txt";
		ifstream FIN; FIN.open(PATH_PATH, ios::in);
		while (!FIN.eof())
		{
			string ssss;
			getline(FIN, ssss);
			if (ssss.size() == 0) break;
			string PATH_PATH_PATH = "data/" + to_string(s->year) + "/" + to_string(s->term) + "/students/" + ssss;
			_mkdir(PATH_PATH_PATH.c_str());
			PATH_PATH_PATH = "data/" + to_string(s->year) + "/" + to_string(s->term) + "/students/" + ssss + "/class.txt";
			ofstream FOUT(PATH_PATH_PATH);
			FOUT << sss;
			FOUT.close();
		}
		FIN.close();
	}

	fin.close();
	//TO


	string path = "data/" + to_string(s->year) + "/" + to_string(s->term) + "/info_Of_Semester.txt";
	ofstream fout(path);

	if (s->term == 1) fout << s->term << " " << s->year << endl;
	if (s->term == 2) fout << s->term << " " << s->year << endl;
	if (s->term == 3) fout << s->term << " " << s->year << endl;

	fout << s->startDate.day << " " << s->startDate.month;
	fout << " " << s->startDate.year << endl;

	fout << s->endDate.day << " " << s->endDate.month;
	fout << " " << s->endDate.year << endl;

	fout.close();

	path = "data/cache/currentSemester.txt";
	fout.open(path);

	if (s->term == 1) fout << s->term << " " << s->year << endl;
	if (s->term == 2) fout << s->term << " " << s->year << endl;
	if (s->term == 3) fout << s->term << " " << s->year << endl;

	fout << s->startDate.day << " " << s->startDate.month;
	fout << " " << s->startDate.year << endl;

	fout << s->endDate.day << " " << s->endDate.month;
	fout << " " << s->endDate.year << endl;
	fout.close();

	path = "csvFile/" + to_string(s->year) + "/" + to_string(s->term) + "/info_Of_Semester.txt";
	fout.open(path);

	if (s->term == 1) fout << s->term << " " << s->year << endl;
	if (s->term == 2) fout << s->term << " " << s->year << endl;
	if (s->term == 3) fout << s->term << " " << s->year << endl;

	fout << s->startDate.day << " " << s->startDate.month;
	fout << " " << s->startDate.year << endl;

	fout << s->endDate.day << " " << s->endDate.month;
	fout << " " << s->endDate.year << endl;
	fout.close();
	cout << "\n\n\n\n";
	Pull();
}

void CourseRegister(int semester, int year)
{

	string path = "data/" + to_string(year) + "/" + to_string(semester) + "/courseRegister.txt";
	ofstream fout(path);
	Date start, end;
	cin >> start.day >> start.month >> start.year;
	cin >> end.day >> end.month >> end.year;



	fout << start.day << " " << start.month << " " << start.year << endl;
	fout << end.day << " " << end.month << " " << end.year << endl;

	fout.close();

	path = "data/cache/courseRegister.txt";
	fout.open(path);

	fout << start.day << " " << start.month << " " << start.year << endl;
	fout << end.day << " " << end.month << " " << end.year << endl;

	fout.close();
}