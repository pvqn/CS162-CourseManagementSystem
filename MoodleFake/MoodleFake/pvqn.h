#pragma once
#include "struct.h"
Date getcurrentdate();
bool compare(Date cur, Date start, Date end);
void displaycourse_student(Course* display, int i);
void viewcourse_student(Semester* head, string id);
void viewclass(Class* head);
string displaysession(string id);
void displaylogin(string& user, string& password);
void removedenrolledcourse(Semester* now, string id);
bool displaymenu(bool isstudent);
Semester* getdatafromcache(Date& startreg, Date& endreg);
void enrolledcoure(Semester* now, string id);
void viewenrolledcourse(Semester* now, string id);