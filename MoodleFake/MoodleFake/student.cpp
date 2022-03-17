#include "student.h"
#include "classes.h"
void ViewClass( Class *ClassList ) // view HS trong lop
{
    string Name;
    cout << "Enter class name: "; cin >> Name;
    Class *cur = ClassList;
    while( cur && cur->ClassName != Name ) cur = cur->next;
    if( !cur )
    {
        cout << "The class is not exist.";
        return;
    }
    Student *Person = cur->StudentList;
    int index = 0;
    while( Person )
    {
        cout << (++index) << ". " << Person->firstName << ' ' << Person->lastName << '\n';
        Person = Person->next;
    }
}
