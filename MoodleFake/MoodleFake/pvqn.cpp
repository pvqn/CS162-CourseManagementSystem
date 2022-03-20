#include <ctime>
#include "struct.h"
using namespace std;
Date getcurrentdate () {
    time_t t = time(0);   // get time now
    tm* now = localtime(&t);
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
                        if (!i)
                        {
                            cout << "Courses in this semester: " << endl;
                        }
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
void viewclass(Class* head)
{
    int i = 0;
    cout << "Here is the list of classes" << endl;
    while (head)
    {
        cout << i + 1 << ". " << head->ClassName << endl;
        head = head->next;
        ++i;
    }
}
/* pass string id
* kiểm tra đã đăng kí bao nhiêu course
* kiểm tra có giờ nào chung không
* xu li chinh
*   in ra list cac khoa hoc hoc ki nay mo, cho hoc sinh chon so
*   kiem tra hoc sinh da co trong lop hoc nay chua
*   kiem tra co trung session hay kong
*   kiem tra co qua 5 course hay khong
*   neu tat ca deu khong, them student id vao cuoi student list
*/
// xu li dang ki hoc phan
bool checkhowmanycourse(Semester* now, string id)
{
    int sum = 0;
    Course* cur = now->course_cur;
    while (cur)
    {
        student_list* pcur = cur->student;
        while (pcur)
        {
            if (pcur->id == id)
            {
                ++sum;
                break;
            }
            pcur = pcur->next;
        }
        cur = cur->next;
    }
    if (sum >= 5) return false;
    return true;
}
bool issamesession(Semester* now, string id, string s1, string s2, Course*cur)
{
    Course* current = now->course_cur;
    while (current)
    {
        student_list* pcur = current->student;
        while (pcur)
        {
            if (pcur->id == id && current->ses1 == s1 &&
                current->ses2 == s2 && current != cur)
            {
                return true;
            }
            pcur = pcur->next;
        }
        current = current->next;
    }
    return false;
}
bool isstudentexisted(Course* cur, string id)
{
    student_list *pcur = cur->student;
    while (pcur)
    {
        if (pcur->id == id)
            return true;
        pcur = pcur->next;
    }
    return false;
}
void displaymenuforcourseregistration(Semester* now)
{
    Course* pcur = now->course_cur;
    int i = 0;
    while (pcur)
    {
        if (!i)
        {
            cout << "Courses in this semester: " << endl;
        }
        displaycourse_student(pcur, i);
        pcur = pcur->next;
    }
}
Course* findcourse(Semester* now, int i)
{
    int t = 1;
    Course* pcur = now->course_cur;
    while (t != i)
    {
        pcur = pcur->next;
    }
    return pcur;
}
void enrolledcoure(Semester* now, string id)
{
    displaymenuforcourseregistration(now);
    while (true)
    {
        int i = 0;
        cout << "enter the number to enroll a course, press 0 to stop: ";
        cin >> i;
        if (!i) break;
        Course* find = findcourse(now, i);
        if (!isstudentexisted(find, id)
            && !issamesession(now, id, find->ses1, find->ses2, find)
            && checkhowmanycourse(now, id))
        {
            student_list* pcur = find->student;
            if (!pcur)
            {
                pcur = new student_list;
                pcur->id = id;
            }
            else
            {
                while (pcur->next)
                {
                    pcur = pcur->next;
                }
                pcur->next = new student_list;
                pcur = pcur->next;
                pcur->id = id;
            }
        }
    }
}