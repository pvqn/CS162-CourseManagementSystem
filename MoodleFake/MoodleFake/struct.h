#pragma once
#include <string>
#include <fstream>
#include <iostream>
//#include <string>
#include <direct.h>
#include <ctime>
#include <conio.h>
#include <Windows.h>
using namespace std;
struct Date {
	int day, month, year;

	//Constructor
	//Dễ sử dụng hơn, không cần mỗi lần gọi Date phải code Date.day, Date.month, Date.year
	//Ví dụ 1/1/2022 thì Date(1, 1, 2022)
	Date(int day = -1, int month = -1, int year = -1) : day(day), month(month), year(year) {};
};
struct Student {
	Student* next=nullptr;
	string id;
	string firstName;
	string lastName;
	string gender;
	Date dob; // date of birth
	string socialId;
	string courseID;
};
struct User {
	User* next=nullptr;
	string username;
	string password;
	string role;
	string Class;
};
struct Mark {
	float totalMark=0;
	float finalMark=0;
	float midtermMark=0;
	float otherMark=0;
};
struct Class
{
	Class* next=nullptr;                   // Create "ClassList" for searching
	Student* StudentList = nullptr;           // Create "StudentList"
	string ClassName;
};
struct student_list
{
	string id;
	Mark mark;
	student_list* next = nullptr;
};
struct Course
{
	string id;
	string name;
	string teacher;
	int nCredits;
	int maxCapacity;
	string day1, ses1;
	string day2, ses2;
	student_list* student = nullptr;
	Course* next = nullptr;
};
struct Semester {
	int year, term;
	Date startDate, endDate;
	// doi date * thanh date
	Course* course_cur = nullptr;
	Semester* next = nullptr;

};