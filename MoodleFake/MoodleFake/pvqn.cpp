#include <ctime>
#include "date.h"
#include "semester.h"
#include "course.h"
Date* getcurrentdate () {
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    Date* cur = new Date;
    cur->year = now->tm_year + 1900;
    cur->month = now->tm_mon + 1;
    cur->day = now->tm_mday;
    return cur;
}

void viewcourse_student(Semester *head)
{
    Date* cur = getcurrentdate();
    while (head)
    {
        
    }
}