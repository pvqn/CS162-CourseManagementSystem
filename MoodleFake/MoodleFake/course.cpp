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
void updateCourse(Course* pCur, string id)
{

}

