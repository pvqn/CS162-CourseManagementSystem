#include "struct.h"
#include "pvqn.h"

void displayclass_student() // display class students
{
    system("clrscr");

    string Classname;
    cout << "Enter class name: "; cin >> Classname;

    string path = "data/classes/classList.txt";
    ifstream fin(path);
    bool Find = false;
    while (!fin.eof())
    {
        string Name;
        fin >> Name;
        if (Name == Classname)
        {
            Find = true;
            break;
        }
    }
    fin.close();

    if (!Find)
    {
        cout << "This class is not exist !";
        return;
    }

    path = "data/classes/" + Classname + "/studentList.txt";
    fin.open(path);
    cout << "Student list of this class: " << '\n';
    int index = 0;
    while (!fin.eof())
    {
        string Name;
        fin >> Name; 
        cout << ++index << ' ' << Name << '\n';
    }
    fin.close();
}

/*
void ViewCourseList( Course *CourseList ) // Danh sach khoa hoc
{
    Course *cur = CourseList;
    while( cur )
    {
        cout << cur->id << ": " << cur->name << '\n';   // Print ID and name
        cur = cur->next;
    }
}
*/