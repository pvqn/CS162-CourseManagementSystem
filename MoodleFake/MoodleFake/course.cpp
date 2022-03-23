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


