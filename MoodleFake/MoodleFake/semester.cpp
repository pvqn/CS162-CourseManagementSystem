#include "struct.h"
void setCurrentSemester(int year, int term, Date start, Date end) {
	string path = "data/" + to_string(year) + '/' + to_string(term) + "/info.txt";
	ofstream fout(path);
	fout << year << '\n';
	fout << term << '\n';
	fout << start.day << ' ' << start.month << ' ' << start.year << '\n';
	fout << end.day << ' ' << end.month << ' ' << end.year << '\n';
	fout.close();

	path = "data/cache/currentSemester.txt";
	fout.open(path);
	fout << year << '\n';
	fout << term << '\n';
	fout << start.day << ' ' << start.month << ' ' << start.year << '\n';
	fout << end.day << ' ' << end.month << ' ' << end.year << '\n';
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