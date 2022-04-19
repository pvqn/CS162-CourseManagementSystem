#include "staff.h"
#include "struct.h"
#include "pvqn.h"
#include "user.h"
#include "display.h"
#include <iomanip>
#include <iostream>
#include <Windows.h>

void viewScoreboard()
{
    // Get student ID of the user
    string studentID;
    ifstream fin; ofstream fout;
    string path_in = "data/cache/currentUser.txt";
    fin.open(path_in);
    fin >> studentID;
    fin.close();

    // Print score board
    cout << "Student ID: " << studentID << '\n' << '\n';
    path_in = "data/cache/Semester/students/" + studentID + "/course.txt";

    cout << setw(20) << right << ' '; cout << '|';
    cout << setw(6) << left << "Total"; cout << '|';
    cout << setw(6) << left << "Final"; cout << '|';
    cout << setw(6) << left << "Mid"; cout << '|';
    cout << setw(6) << left << "Other"; cout << '|' << '\n';
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
        fin_mark >> Total >> Final >> Mid >> Other;
        fin_mark.close();

        cout << setw(20) << right << course_name; cout << '|';
        cout << setw(6) << left << Total; cout << '|';
        cout << setw(6) << left << Final; cout << '|';
        cout << setw(6) << left << Mid; cout << '|';
        cout << setw(6) << left << Other; cout << '|';

    }
    fin.close();
}

bool studentChoice(int& choice, User*& account, string& username, string& password, Class*& classes, Student* student) {
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
        case 7: // view student result
            viewScoreboard();
            break;
        case 8: //Log out
            return 1;
        default:
            break;
        }
        cout << endl;
        cout << "\npress enter to continue...";
        _getch();
        HANDLE hStdout;
        hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        cls(hStdout);

        displaymenu(1);
    } while (choice != 9);
    return 0;
}