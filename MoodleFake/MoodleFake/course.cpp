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

	//cout << cCur->id << " " << cCur->name << " " << cCur->teacher << endl;
	return cCur;
}
void addCourse(Course*& pCourse)
{
	Semester* s = new Semester;
	string PATHPATH = "data/cache/currentSemester.txt";
	ifstream FIN(PATHPATH);
	FIN >> s->term >> s->year;
	FIN >> s->startDate.day >> s->startDate.month >> s->startDate.year;
	FIN >> s->endDate.day >> s->endDate.month >> s->endDate.year;
	FIN.close();
	cout << s->term << "CHECK" << endl;
	Course* tmp = new Course;
	Course* pCur = pCourse;
	Course* newCourse = add();
	//cout << "CHECK" << endl;
	string path = "data/" + to_string(s->year) + "/" + to_string(s->term) + "/courseList.txt";
	//cout << "CHECK" << endl;

	ifstream fin(path);
	while (!fin.eof())
	{
		string STR;
		getline(fin, STR);
		if (STR.size() == 0) break;
		if (STR == newCourse->id)
		{
			cout << "Failed to add a new course!!\n";
			cout << "The course you want to add has already existed!!\n";
			system("pause");
			return;
		}
		cout << "CHECK" << endl;
	}
	fin.close();
	//cout << "CHECK" << endl;

	string PATH = "data/" + to_string(s->year) + "/" + to_string(s->term) + "/coureses/" + newCourse->id;
	_mkdir(PATH.c_str()); // tao file course ID

	path = "data/" + to_string(s->year) + "/" + to_string(s->term) + "/coureses/" + newCourse->id + "/info_Of_Course.txt";
	ofstream fout(path);
	fout << newCourse->name << endl;
	fout << newCourse->teacher << endl;
	fout << newCourse->nCredits << endl;
	fout << newCourse->maxCapacity << endl;
	string str1 = displaysession(newCourse->day1 + newCourse->ses1);
	string str2 = displaysession(newCourse->day2 + newCourse->ses2);
	//cout << "CHECK" << endl;
	fout << str1 << endl;
	fout << str2 << endl;
	fout.close();
	//cout << newCourse->maxCapacity << endl;
	//cout << "CHECK" << endl;

	path = "data/" + to_string(s->year) + "/" + to_string(s->term) + "/courseList.txt";
	fout.open(path, ios::app);
	fout << newCourse->id << endl;
	fout.close();

	while (pCur != nullptr)
	{
		if (pCur->id == newCourse->id)
		{
			cout << "Failed to add a new course!!\n";
			cout << "The course you want to add has already existed!!\n";
			system("pause");
			return;
		}
		tmp = pCur;
		pCur = pCur->next;
	}
	if (pCourse == nullptr)
	{
		pCourse = newCourse;
		//cout << pCourse->maxCapacity << endl;
		return;
	}
	pCur = newCourse;
	tmp->next = pCur;

	delete s;
}

void view_Course(Course* pCur)
{
	Semester* s = new Semester;
	string PATHPATH = "data/cache/currentSemester.txt";
	ifstream FIN(PATHPATH);
	FIN >> s->term >> s->year;
	FIN >> s->startDate.day >> s->startDate.month >> s->startDate.year;
	FIN >> s->endDate.day >> s->endDate.month >> s->endDate.year;
	FIN.close();

	string path = "data/" + to_string(s->year) + "/" + to_string(s->term) + "/courseList.txt";
	ifstream fin;
	fin.open(path, ios::in);
	while (!fin.eof())
	{
		string STR;
		getline(fin, STR);

		if (STR.size() == 0) break;

		cout << "CHECK CHECK" << endl;
		cout << STR << endl;
		string PATH = "data/" + to_string(s->year) + "/" + to_string(s->term) + "/coureses/" + STR + "/info_Of_Course.txt";
		ifstream FIN;
		FIN.open(PATH, ios::in);
		Course* cCur = new Course;

		cout << STR << endl;
		getline(FIN, cCur->name); cout << cCur->name << endl;
		getline(FIN, cCur->teacher); cout << cCur->teacher << endl;
		FIN >> cCur->nCredits; cout << cCur->nCredits << endl;
		FIN >> cCur->maxCapacity; cout << cCur->maxCapacity << endl;
		FIN.ignore();
		getline(FIN, cCur->day1); getline(FIN, cCur->ses1);
		getline(FIN, cCur->day2); getline(FIN, cCur->ses2);
		cout << cCur->day1 << " " << cCur->ses1 << endl;
		cout << cCur->day2 << " " << cCur->ses2 << endl;

		FIN.close();
	}

	fin.close();
	delete s;
	/*cin.ignore();
		cout << "Input id: ";  getline(cin, cCur->id);
		cout << "Input Name: "; getline(cin, cCur->name);
		cout << "Input Teacher: "; getline(cin, cCur->teacher);
		cout << "Input Number of Credits: ";  cin >> cCur->nCredits;
		cout << "Input max students: ";  cin >> cCur->maxCapacity;
		cin.ignore();
		cout << "Day1: "; getline(cin, cCur->day1);
		cout << "Ses1: "; getline(cin, cCur->ses1);
		cout << "Day2: "; getline(cin, cCur->day2);
		cout << "Ses2: "; getline(cin, cCur->ses2);*/
}
void updateCourse(Course*& pCourse)
{
	Semester* s = new Semester;
	string PATHPATH = "data/cache/currentSemester.txt";
	ifstream FIN(PATHPATH);
	FIN >> s->term >> s->year;
	FIN >> s->startDate.day >> s->startDate.month >> s->startDate.year;
	FIN >> s->endDate.day >> s->endDate.month >> s->endDate.year;
	FIN.close();
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
		//system("cls");
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
	string path = "data/" + to_string(s->year) + "/" + to_string(s->term) + "/coureses/" + pCur->id + "/info_Of_Course.txt";
	ofstream fout(path);
	fout << pCur->name << endl;
	fout << pCur->teacher << endl;
	fout << pCur->nCredits << endl;
	fout << pCur->maxCapacity << endl;
	string str1 = displaysession(pCur->day1 + pCur->ses1);
	string str2 = displaysession(pCur->day2 + pCur->ses2);
	//cout << "CHECK" << endl;
	fout << str1 << endl;
	fout << str2 << endl;
	fout.close();
	cout << "Update successfully !!" << endl;

	delete s;
}

void DeleteCourse(Course*& pCourse, Semester* s)
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
		//system("cls");
		if (option > 2 || option < 1)
		{
			cout << "Please input again" << endl << endl;
			continue;
		}
		else break;
	}
	if (option == 2) return;
	/*cout << "CHECK" << endl;
	string path = "data/" + to_string(s->year) + "/" + to_string(s->term) + "/coureses/" + id;
	cout << _rmdir(path.c_str()) << endl;
	_rmdir(path.c_str());*/

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

