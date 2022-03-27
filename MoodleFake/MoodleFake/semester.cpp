// HEAD
#include "struct.h"
//void setCurrentSemester(int year, int term, Date start, Date end) {
//	string path = "data/" + to_string(year) + '/' + to_string(term) + "/info.txt";
//	ofstream fout(path);
//	fout << year << endl;
//	fout << term << endl;
//	fout << start.day << ' ';
//	fout << start.month << ' ';
//	fout << start.year << endl;
//	fout << end.day << ' ';
//	fout << end.month << ' ';
//	fout << end.year << endl;
//	fout.close();
//
//	path = "data/cache/currentSemester.txt";
//	fout.open(path);
//	fout << year << endl;
//	fout << term << endl;
//
//	fout << start.day << ' ';
//	fout << start.month << ' ';
//	fout << start.year << ' ' << endl;
//		
//	fout << end.day << ' ';
//	fout << end.month << ' ';
//	fout << end.year << endl;
//	fout.close();
//
//	path = "data/" + to_string(year) + '/' + to_string(term);
//	_mkdir(path.c_str());
//	path = "data/" + to_string(year) + '/' + to_string(term) + "/courses";
//	_mkdir(path.c_str());
//	path = "data/" + to_string(year) + '/' + to_string(term) + "/students";
//	_mkdir(path.c_str());
//
//
//	path = "csvFile/" + to_string(year) + '/' + to_string(term);
//	_mkdir(path.c_str());
//}
//void inputCurrentSemester(Semester& sem)
//{
//	ifstream fin;
//	fin.open("input_semester.txt");
//
//	fin >> sem.year >> sem.term;
//	fin >> sem.startDate.day >> sem.startDate.month >> sem.startDate.year;
//	fin >> sem.endDate.day >> sem.endDate.month >> sem.endDate.year;
//	
//	
//
//}

//void setCurrentSemester(int year, int term, Date start, Date end)
//{
//	ofstream fout;
//	fout.open("ouput_semester.txt");
//
//}
void setCurrentSemester(int year, int term, Date start, Date end) {
	string path = "data/" + to_string(year) + '/' + to_string(term) + "/info_Of_Semester.txt";
	ofstream fout(path);
//>>>>>>> 4721181f85f83214196216fde0364355879f3ba6
	fout << year << endl;
	fout << term << endl;
	fout << start.day << ' ';
	fout << start.month << ' ';
	fout << start.year << endl;
	fout << end.day << ' ';
	fout << end.month << ' ';
	fout << end.year << endl;

	fout.close();
//<<<<<<< HEAD


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
void Create_newSemester(Semester* Scur)
{
	Semester* s = nullptr;

	
	cin >> s->year >> s->term;
	cin >> s->startDate.day >> s->startDate.month >> s->startDate.year;
	cin >> s->endDate.day >> s->endDate.month >> s->endDate.year;
	//s->Course

	Scur = s; /// Since we just need to create one semester

	string path = "data/" + to_string(s->year) +"/"+ to_string(s->term) + "/info_Of_Semester.txt";
	ofstream fout(path);

	if (s->term == 1) fout << s->term << "/" << s->year << endl;
	if (s->term == 2) fout << s->term << "/" << s->year << endl;
	if (s->term == 3) fout << s->term << "/" << s->year << endl;

	fout << s->startDate.day << "/" << s->startDate.month;
	fout << "/" << s->startDate.year << endl;

	fout << s->endDate.day << "/" << s->endDate.month;
	fout << "/" << s->endDate.year << endl;

	fout.close();

	path = "data/cache/currentSemester.txt";
	fout.open(path);

	if (s->term == 1) fout << s->term << "/" << s->year << endl;
	if (s->term == 2) fout << s->term << "/" << s->year << endl;
	if (s->term == 3) fout << s->term << "/" << s->year << endl;

	fout << s->startDate.day << "/" << s->startDate.month;
	fout << "/" << s->startDate.year << endl;

	fout << s->endDate.day << "/" << s->endDate.month;
	fout << "/" << s->endDate.year << endl;
	fout.close();
}

void CourseRegister(Date& start, Date& end, int semester)
{

	string path = "data/"+ to_string(semester) + "/courseRegister.txt";
	ifstream fin(path);
	
	fin >> start.day >> start.month >> start.year;
	fin >> end.day >> end.month >> end.year;

	fin.close();
}