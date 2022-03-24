#include "struct.h"

void addCourse(Course* pCourse, Course* newCourse)
{
	Course* pCur = pCourse;

	while (pCur != nullptr)
	{
		if (pCur->id == newCourse->id)
		{
			cout << "Failed to add a new course!!\n";
			cout << "The course you want to add has already existed!!\n";
			system("pause");
			system("cls");
			return;
		}
		pCur = pCur->next;
	}
	if (pCourse == nullptr)
	{
		pCourse = newCourse;
		return;
	}
	pCur->next = newCourse;
	pCur = pCur->next;
}

void view_Course(Course* pCur, Semester* Scur)
{
	string path = "data/" + to_string(Scur->year) + "/" + to_string(Scur->term) + "/courses/courseList.txt";
	ofstream fout(path);
	while (pCur != nullptr)
	{
		fout << pCur->id << endl;
		fout << pCur->name << endl;
		fout << pCur->teacher << endl;
		fout << pCur->nCredits << endl;
		fout << pCur->maxCapacity << endl;
		fout << pCur->day1 << " : " << pCur->ses1 << endl;
		fout << pCur->day2 << " : " << pCur->ses2 << endl;
		pCur = pCur->next;
	}
	fout.close();
}
void updateCourse(Course* pCourse, string id)
{
	Course* pCur = pCourse;
	while (pCur != nullptr && pCur->id != id)
	{
		pCur = pCur->next;
	}
	int option;
	while (true)
	{
		cout << "0: Back " << endl;
		cout << "Input your option you want:  " << endl;
		cout << "1. Course's ID" << endl;
		cout << "2. Course's Name" << endl;
		cout << "3. Teacher's Name" << endl;
		cout << "4. Number of Credits" << endl;
		cout << "5. Max of Students " << endl;
		cout << "6. New days and new sessions" << endl;
		cout << "Which infomation do you want to update: " << endl << endl;

		cout << "Your Input: "; 
		cin >> option;
		system("cls");
		if (option > 6 || option < 0)
		{
			cout << "Please input again" << endl << endl;
			continue;
		}
	}
	if (option == 0) return;

	if (option == 1)
	{
		cout << "New course's ID: ";
		cin.ignore();
		getline(cin, pCur->id);
	}
	if (option == 2)
	{
		cout << "New course's Name: ";
		cin.ignore();
		getline(cin, pCur->name);
	}
	if (option == 3)
	{
		cout << "New teacher's Name: ";
		cin.ignore();
		getline(cin, pCur->teacher);
	}
	if (option == 4)
	{
		cout << "New number of credits: ";
		cin >> pCur->nCredits;
	}
	if (option == 5)
	{
		cout << "Max of students ";
		cin >> pCur->maxCapacity;
	}
	if (option == 6)
	{
		cout << "New day 1 and new session 1: ";
		cin.ignore();
		getline(cin, pCur->day1);
		getline(cin, pCur->ses1);
		cout << "New day 2 and new session 2: ";
		getline(cin, pCur->day2);
		getline(cin, pCur->ses2);
	}

	cout << "Update successfully !!" << endl;

	system("pause");
	system("cls");
}

