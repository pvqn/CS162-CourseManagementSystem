#pragma once
#include <string>
#include "student.h"
using namespace std;

struct Class
{
    Class *next;                   // Create "ClassList" for searching
    Student *StudentList;           // Create "StudentList"
    string ClassName;
};

void createClass(string className);

