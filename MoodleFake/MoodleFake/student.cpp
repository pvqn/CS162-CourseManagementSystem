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

void displaycourse_list() // In ra danh sach cac khoa hoc
{
    // Find the year and the semester
    Date today = getcurrentdate();
    int Year = today.year, Term = 0;
    if (today.month < 9) --Year;
    ifstream fin;
    for (int i = 1; i <= 3; ++i)
    {
        string path = "data/" + to_string(Year) + "/" + char(i+48) +"/info_Of_Semester.txt";
        fin.open(path);
        Date Start, End;
        fin >> Start.day >> Start.month >> Start.year;
        fin >> End.day >> End.month >> End.year;
        fin.close();
        if (compare(today, Start, End))
        {
            Term = i;
            break;
        }
    }
    // Print the course list of this semester
    string path = "data/" + to_string(Year) + '/' + to_string(Term) + "/courseList.txt";
    fin.open(path);
    while (!fin.eof())
    {
        string cur;
        fin >> cur;
        cout << cur << '\n';
    }
    fin.close();
}