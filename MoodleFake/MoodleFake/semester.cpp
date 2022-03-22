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
void setCurrentSemester(int year, int term, Date start,Date end)
{
	ofstream fout;
	fout.open("ouput_semester.txt");

	fout << year << endl;
	fout << term << endl;
	fout << start.day << ' ';
	fout << start.month << ' ';
	fout << start.year << endl;
	fout << end.day << ' ';
	fout << end.month << ' ';
	fout << end.year << endl;

	fout.close();
}