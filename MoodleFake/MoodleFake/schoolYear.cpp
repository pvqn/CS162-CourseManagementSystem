#include "struct.h"
#include <ctime>

void setCurrentYear(int year) {
    string path = "data/" + to_string(year);
    _mkdir(path.c_str());

    path = "csvFile/" + to_string(year);
    _mkdir(path.c_str());

    //path = "data/cache/currentYear.txt";
    //ofstream fout(path);
    //fout << year;
    //fout.close();
}

int getCurrentYear() {
    time_t current_time;
    current_time = time(NULL);
    int year;
    year = 1970 + current_time / 31537970;
    return year;
}