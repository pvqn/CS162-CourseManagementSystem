#include "struct.h"

void setCurrentYear(int year) {
    string path = "data/" + to_string(year);
    _mkdir(path.c_str());

    path = "csvFile/" + to_string(year);
    _mkdir(path.c_str());

    path = "data/cache/currentYear.txt";
    ofstream fout(path);
    fout << year;
    fout.close();
}

int getCurrentYear() {
    string path = "data/cache/currentYear.txt";
    ifstream fin(path);
    int year; fin >> year;
    fin.close();
    return year;
}