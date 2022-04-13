#include "staff.h"
#include "struct.h"
#include "pvqn.h"
#include "user.h"
#include <iomanip>
#include <iostream>

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
    // Print the course list of this semester
    string path = "data/cache/Semester/coureses/courseList.txt";
    ifstream fin;
    fin.open(path);
    while (!fin.eof())
    {
        string cur;
        fin >> cur;
        cout << cur << '\n';
    }
    fin.close();
}

void displaycourse_studentList()
{
    
    // Print student in this course
    string Course_name;
    cout << "Please enter course name ( Example CS162 ): "; cin >> Course_name;
    string path = "data/cache/Semester/coureses/courseList.txt";
    bool Check = false;
    ifstream fin;
    fin.open(path);
    while (!fin.eof())
    {
        string cur; fin >> cur;
        if (cur == Course_name) Check = true;
    }
    fin.close();
    if (!Check)
    {
        cout << "Your finding course is not exist !";
        return;
    }
    path = "data/cache/Semester/coureses" + Course_name + "/studentList.txt";
    fin.open(path);
    while (!fin.eof())
    {
        string ID, Name;
        fin >> ID;
        fin.ignore(); getline(fin, Name);
        cout << ID << ' ' << Name << '\n';
    }
    fin.close();
}

void viewScoreboard()
{
    // Get student ID of the user
    string studentID;
    ifstream fin; ofstream fout;
    string path_in = "data/cache/currentUser.txt";
    fin.open(path_in);
    getline(fin, studentID);
    fin.close();

    // Print score board
    cout << "Student ID: " << studentID << '\n' << '\n';
    path_in = "data/cache/Semester/students/" + studentID + "/course.txt";

    cout << setw(20) << right << ' '; cout << '|';
    cout << setw(6) << left << "Total"; cout << '|';
    cout << setw(6) << left << "Mid"; cout << '|';
    cout << setw(6) << left << "Final"; cout << '|';
    cout << setw(6) << left << "Other"; cout << '|';
    cout << setfill('-');		// set fill bang ky tu '-' thay vi ' '
    cout << setw(49) << "-" << endl;	// fill 49 ky tu '-'
    cout << setfill(' ');

    fin.open(path_in);
    while (!fin.eof())
    {
        string course_name;
        getline(fin, course_name);
        if (course_name.size() == 0) break;

        float Total, Mid, Final, Other;
        ifstream fin_mark;
        string path_mark = "data/cache/Semester/students/" + studentID + "/" + course_name + "_mark.txt";
        fin_mark.open(path_mark);
        fin_mark >> Total >> Mid >> Final >> Other;
        fin_mark.close();

        cout << setw(20) << right << course_name; cout << '|';
        cout << setw(6) << left << Total; cout << '|';
        cout << setw(6) << left << Mid; cout << '|';
        cout << setw(6) << left << Final; cout << '|';
        cout << setw(6) << left << Other; cout << '|';

    }
    fin.close();
}

void studentChoice(int& choice, User*& account, string& username, string& password, Class*& classes, Student* student) {
    Date startreg, endreg;
    Semester* s = getdatafromcache(startreg, endreg);
    do {
        cout << "\nInput your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1: //View info 
            viewUserProfile(account);
            break;
        case 2: //Change password
            changePass(account);
            break;
        case 3: //Enroll in a course
            if (compare(getcurrentdate(), startreg, endreg))
                enrolledcoure(s, account->username);
            else std::cout << "out of time for course registration";
            break;
        case 4: //View a list of enrolled courses
            viewenrolledcourse(s, account->username);
            break;
        case 5: //remove a course
            removedenrolledcourse(s, account->username);
            break;
        case 6: //view a list of courses in this semester
            viewcourse_student(s, account->username);
            break;
        case 7: //Log out
            displaylogin(username, password);
            if (displaymenu(login(username, password, account)))
                studentChoice(choice, account, username, password, classes, student); // student
            else // staff
                staffChoice(choice, account, username, password, classes, student);
        default:
            break;
        }
    } while (choice != 8);
}