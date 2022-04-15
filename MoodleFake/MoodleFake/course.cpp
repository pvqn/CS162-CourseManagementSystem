#include "struct.h"
#include "pvqn.h"
Course* add()
{
	Course* cCur = new Course;
	cin.ignore();
	cout << "Input id: ";  getline(cin, cCur->id);
	cout << "Input Name: "; getline(cin, cCur->name);
	cout << "Input Teacher: "; getline(cin, cCur->teacher);
	cout << "Input Number of Credits: ";  cin >> cCur->nCredits;
	cout << "Input max students: ";  cin >> cCur->maxCapacity;
	cin.ignore();
	cout << "Day1: "; getline(cin, cCur->day1);
	cout << "Ses1: "; getline(cin, cCur->ses1);
	cout << "Day2: "; getline(cin, cCur->day2);
	cout << "Ses2: "; getline(cin, cCur->ses2);

	cout << cCur->id << " " << cCur->name << " " << cCur->teacher << endl;
	return cCur;
}
void addCourse(Course*& pCourse)
{
	Course* pCur = pCourse;
	Course* newCourse = add();
	//cout << newCourse->maxCapacity << endl;
	while (pCur != nullptr)
	{
		if (pCur->id == newCourse->id)
		{
			cout << "Failed to add a new course!!\n";
			cout << "The course you want to add has already existed!!\n";
			system("pause");
			return;
		}
		pCur = pCur->next;
	}
	if (pCourse == nullptr)
	{
		pCourse = newCourse;
		//cout << pCourse->maxCapacity << endl;
		return;
	}
	pCur->next = newCourse;
	pCur = pCur->next;
}

void view_Course(Course* pCur, Semester* Scur)
{
	while (pCur != nullptr)
	{
		cout << pCur->id << endl;
		cout << pCur->name << endl;
		cout << pCur->teacher << endl;
		cout << pCur->nCredits << endl;
		cout << pCur->maxCapacity << endl;
		string str1 = displaysession(pCur->day1 + pCur->ses1);
		string str2 = displaysession(pCur->day2 + pCur->ses2);
		cout << str1 << endl;
		cout << str2 << endl;
		pCur = pCur->next;
	}
}
void updateCourse(Course* pCourse)
{
	string id;
	cin.ignore();
	getline(cin, id);
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
		else break;
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

void DeleteCourse(Course* pCourse)
{
	string id;
	cin.ignore();
	getline(cin, id);
	Course* pCur = pCourse;
	Course* pBefore_Cur = nullptr;
	while (pCur->id != id && pCur != nullptr)
	{
		pBefore_Cur = pCur;
		pCur = pCur->next;
	}
	if (pCur == nullptr) return;

	int option;
	while (true)
	{
		cout << "Are you sure to delete this course: " << endl;
		cout << "Input your option: " << endl;
		cout << "1. Yes" << endl;
		cout << "2. No" << endl;
		cin >> option;
		system("cls");
		if (option > 2 || option < 1)
		{
			cout << "Please input again" << endl << endl;
			continue;
		}
		else break;
	}
	if (option == 2) return;
	
	if (pBefore_Cur == nullptr)
	{
		pBefore_Cur = pCur->next;
		delete pCur;
	}
	else
	{
		pBefore_Cur->next = pCur->next;
		delete pCur;
	}

}

