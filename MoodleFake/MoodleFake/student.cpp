#include "struct.h"
#include "pvqn.h"

void displayclass_student() // display class students
{
    system("clrscr");

    string Classname;
    cout << "Enter class name: "; cin >> Classname;
    // Find class is exit or not
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
    // The case: class is not exist
    if (!Find)
    {
        cout << "This class is not exist !";
        return;
    }
    // Create student list ID
    path = "data/classes/" + Classname + "/studentID.txt";
    fin.open(path);
    int Number_of_student; cin >> Number_of_student;
    int* studentList = new int[Number_of_student];
    for (int i = 0; i < Number_of_student; ++i) cin >> studentList[i];
    delete[] studentList;
    fin.close();
    // Display student information
    for (int i = 0; i < Number_of_student; ++i)
    {
        path = "data/classes/" + Classname + '/' + to_string(studentList[i]) + ".txt";

        int No;
        string ID, First_name, Last_name, socialID;
        bool Gender;
        Date DOB;

        fin.open(path);
        fin >> No >> ID >> First_name;
        fin.ignore(); getline(fin, Last_name);
        fin >> Gender;
        fin >> DOB.day >> DOB.month >> DOB.year;
        fin >> socialID;

        cout << No << ' ' << ID << ' ' << First_name << ' ' << Last_name << '\n';

        fin.close();
    }
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