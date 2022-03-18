#include <ctime>
#include "struct.h"
using namespace std;
Date getcurrentdate () {
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    Date cur;
    cur.year = now->tm_year + 1900;
    cur.month = now->tm_mon + 1;
    cur.day = now->tm_mday;
    return cur;
}
// neu ngay hien tai dang trong ki hoc, return true, else return true
bool compare(Date cur, Date start, Date end)
{
    if (start.year <= cur.year && cur.year <= end.year)
    {
        // cung nam thi compare tiep
        if (start.month <= cur.month && cur.month <= end.month)
        {
            // trong khoang thoi gian hop le
            // cung thang bat dau, so sanh ngay
            if (start.month == cur.month && start.day <= cur.day)
            {
                return true;
            }
            else return false;
            // cung thang ket thuc, so sanh ngay
            if (end.month == cur.month && cur.day <= end.day)
            {
                return true;
            }
            else return false;
            return true;
        }
        return false;
    }
    else return false;
}
void displaycourse_student(Course *display, int i)
{
    if (!i)
    {
        cout << "Courses in this semester: " << endl;
    }
    cout << i + 1 << "." << endl;
    cout << "Course id: " << display->id << endl;
    cout << "Course name: " << display->name << endl;
    cout << "Course's instructor: " << display->teacher << endl;
    cout << "Number of credits: " << display->nCredits << endl;
    cout << "First session: " << display->ses1;
    cout << "Second session: " << display->ses1;
}
void viewcourse_student(Semester *head, string id)
{
    int i = 0;

    Date cur = getcurrentdate(); // bien lay ngay hien tai
    while (head)
    {
        if (compare(cur, head->startDate, head->endDate)) // so sanh
        {
           
            Course* cur = head->course_cur; // khoa hoc hien tai trong ki nay
            while (cur)
            {
                student_list* studentcur = cur->student; // student list trong khoa hoc nay
                while (studentcur)
                {
                    if (studentcur->id == id)
                    {
                        // neu student id co trong khoa nay, them vao mang course[]
                       
                        displaycourse_student(cur, i);
                        ++i;
                        break;
                    }
                    else studentcur = studentcur->next;
                }
                cur = cur->next;
            }
        }
        head = head->next;
    }
}