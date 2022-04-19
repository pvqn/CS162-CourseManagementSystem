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
// MON 1 / TUE 2 / WED 3 / THU 4/ FRI 5/ SAT 6, S1 (07:30) 1, S2 (09:30) 2, S3(13:30) 3 and S4 (15:30) 4
string displaysession(string id)
{
    string d;
    switch (id[0])
    {
    case '1':
        d = "MON ";
        break;
    case '2':
        d = "TUE ";
        break; 
    case '3':
        d = "WED ";
        break;
    case '4':
        d = "THU ";
        break;
    case '5':
        d = "FRI ";
        break;
    case '6':
        d = "SAT ";
        break;
    default:
        break;
    }
    switch (id[1])
    {
    case '1':
        d += "7:30";
        break;
    case '2':
        d += "9:30";
        break;
    case '3':
        d += "13:30";
        break;
    case '4':
        d += "15:30";
        break;
    default:
        break;
    }
    return d;
}
void displaycourse_student(Course *display, int i)
{
    cout << i + 1 << "." << endl;
    cout << "Course id: " << display->id << endl;
    cout << "Course name: " << display->name << endl;
    cout << "Course's instructor: " << display->teacher << endl;
    cout << "Number of credits: " << display->nCredits << endl;
    cout << "First session: " << displaysession(display->ses1) <<endl;
    cout << "Second session: " << displaysession(display->ses2) <<endl;
}
void viewcourse_student(Semester *head, string id)
{
    int i = 0;         
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
void viewclass()
{
    string path = "data/classes/classList.txt";
    ifstream fin;
    fin.open(path);
    string d;
    int i = 0;
    while (fin >> d)
    {
   
       if (!i) 
           cout << "Here is the list of classes" << endl;
           cout << i + 1 << ". " << d << endl;
           ++i;
    }
    
fin.close();
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
// kiểm tra đã đăng kí bao nhiêu course
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
//kiểm tra có giờ nào chung không
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
//  kiem tra hoc sinh da co trong lop hoc nay chua
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
//in ra list cac khoa hoc hoc ki nay mo, cho hoc sinh chon so
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
        ++i;
        pcur = pcur->next;
    }
}
//tim kiem dia chi course duoc chon
Course* findcourse(Semester* now, int i)
{
    int t = 1;
    Course* pcur = now->course_cur;
    while (t != i)
    {
        pcur = pcur->next;
        ++t;
    }
    return pcur;
}
// xu li chinh phan dang ki hoc phan
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
        else cout << "could not enroll this course" << endl;
    }
}
// in ra cac khoa da dang ki
void viewenrolledcourse(Semester* now, string id)
{
    Course* cur = now->course_cur; // khoa hoc hien tai trong ki nay
    int i = 0;
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
                    cout << "Courses that you enrolled: " << endl;
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
// khong dang ki 1 khoa nao do, tuong tu nhu dang ki hoc phan
void removedenrolledcourse(Semester* now, string id)
{
    displaymenuforcourseregistration(now);
    while (true)
    {
        int i = 0;
        cout << "enter the number to remove a course, press 0 to stop: ";
        cin >> i;
        if (!i) break;
        Course* find = findcourse(now, i);
        student_list* pcur = find->student;
        student_list* dummy = new student_list;
        dummy->next = pcur;
        pcur = dummy;
        while (pcur->next)
        {
            if (pcur->next->id == id)
            {
                student_list* temp = pcur->next;
                pcur->next = pcur->next->next;
                delete temp;
                pcur = dummy->next;
                find->student = pcur;
                return;
            }
            else pcur = pcur->next;
        }
    }
}
void displaylogin(string &user, string &password)
{
    cout << "> user: "; cin >> user;
    cout << "> password: "; cin >> password;
}
int displaymenu(int isStudent)
{
    switch (isStudent)
    {
    case 1:
        cout << "1. View info " << endl;
        cout << "2. Change password" << endl;
        cout << "A course registration session is active" << endl;
        cout << "   3. Enroll in a course" << endl;
        cout << "   4. View a list of enrolled courses" << endl;
        cout << "   5. Remove a course" << endl;
        cout << "A course resgistration session is closed" << endl;
        cout << "   6. View a list of courses in this semester" << endl;
        cout << "7. View student result " << endl;
        cout << "8. Log out " << endl;
        cout << "9. Exit program " << endl;
        break;
    case 0:
        cout << "1. View info" << endl;
        cout << "2. Change password" << endl;
        cout << "3. Create a school year" << endl;
        cout << "4. Create a class" << endl;
        cout << "5. Add new students" << endl;
        cout << "Beginning of a semester :" << endl;
        cout << "   6. Create a semester" << endl;
        cout << "   7. Create a course registration" << endl;
        cout << "   8. Add a course to semester" << endl;
        cout << "   9. View the list of courses in the semester" << endl;
        cout << "   10. Update course information" << endl;
        cout << "   11. Delete a course" << endl;
        cout << "12. View a list of classes" << endl;
        cout << "13. View a list of students in a class" << endl;
        cout << "14. View a list of courses in the system" << endl;
        cout << "15. View a list of students in a course" << endl;
        cout << "16. Export a list of students in a course to a csv file" << endl;
        cout << "17. Import the scoreboard of a course" << endl;
        cout << "18. View the scoreboard of a course" << endl;
        cout << "19. View the scoreboard of a class" << endl;
        cout << "20. Log out" << endl;
        cout << "21. Exit program " << endl;
        break;
    default:
        break;
    }
    return isStudent;
}
Semester* getdatafromcache(Date &startreg, Date &endreg)
{
    Semester* s = new Semester;
    Course* head = nullptr;
    string path = "data/cache/Semester/coureses/courseList.txt";
    ifstream fin;
    fin.open(path);
    string id;
    // nhap id cua course hien tai trong semester
    while (fin >> id)
    {
        if (!s->course_cur)
        {
            s->course_cur = new Course;
            head = s->course_cur;
            s->course_cur->id = id;
            fin.ignore();
            getline(fin, s->course_cur->name) ;
        }
        else
        {
            s->course_cur->next = new Course;
            s->course_cur = s->course_cur->next;
            s->course_cur->id = id;
            fin.ignore();
            getline(fin, s->course_cur->name);
        }
    }
    fin.close();
    path = "data/cache/Semester/info_Of_Semester.txt";
    fin.open(path);
    // doc nam hoc, doc hoc ki
    fin >> s->year>>s->term;
    // doc ngay bat dau hoc ki
    fin >> s->startDate.day >> s->startDate.month >> s->startDate.year;
    // doc ngay ket thuc hoc ki
    fin >> s->endDate.day >> s->endDate.month >> s->endDate.year;
    fin.close();
    // doc ngay bat dau dang ki hoc phan
    path = "data/cache/Semester/courseRegister.txt";
    fin.open(path);
    fin >> startreg.day >> startreg.month >> startreg.year;
    fin >> endreg.day >> endreg.month >> endreg.year;
    fin.close();
    // doc thong tin trong cac khoa hoc
    s->course_cur = head;
    Course *cur = head;
    student_list* phead = nullptr;
    while (cur)
    {
        // doc co thong tin trong khoa hoc
            path = "data/cache/Semester/coureses/" + cur->id + "/info_Of_Course.txt";
            fin.open(path);
            getline(fin, cur->teacher);
            fin >> cur->nCredits >> cur->maxCapacity >> cur->ses1 >> cur->ses2;
            fin.close();
        // doc student list trong khoa hoc
            path = "data/cache/Semester/coureses/" + cur->id + "/studentList.txt";
            fin.open(path);
                string input;
                string name; // doc ten nhung khong luu vao 
                student_list *in = cur->student;
                if (fin >> input)
                {
                    in = new student_list;
                    phead = in;
                    in->id = input; 
                    getline(fin, name);
                    fin.ignore();
                    while (fin >> input)
                    {
                            getline(fin, name);
                            fin.ignore();
                            in->next = new student_list;
                            in = in->next;
                            in->id = input;

                    }
                }
            fin.close();
        // doc mark cua student neu co
            path = "data/cache/Semester/coureses/" + cur->id + "/mark.txt";
            fin.open(path);
            student_list* t = cur->student;
            while (t)
            {
                string nul;
                if (fin >> nul)
                {
                    fin >> t->mark.totalMark >> t->mark.finalMark >> t->mark.midtermMark >> t->mark.otherMark;
                }
                else break;
                t = t->next;
            }
            fin.close();
            cur->student = phead;
        cur = cur->next;
       
    } 
   
    return s;
}