#include "struct.h"
void setCurrentSemester(int year, int term, Date start, Date end) {
	string path = "data/" + to_string(year) + '/' + to_string(term) + "/info.txt";
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
}