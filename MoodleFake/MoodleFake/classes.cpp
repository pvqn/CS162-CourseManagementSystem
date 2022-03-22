#include "struct.h"
#include <direct.h>

using namespace std;

void createClass(string className, Class*& classes) {
	//Thêm lớp mới vào linked list của Class
	Class* newClass = new Class;
	newClass->ClassName = className;
	newClass->next = NULL;
	if (classes == NULL) classes = newClass;
	else {
		Class* lastClass = classes;
		while (lastClass->next != NULL)
			lastClass = lastClass->next;
		lastClass->next = newClass;
	}

	//Tạo file chứa class mới
	string path = "data/classes/" + className; // Tạo file class, trong class chứa info học sinh của class đó
	_mkdir(path.c_str()); // Tạo thư mục theo đường dẫn path
	ofstream out;
	out.open("data/classes/classList.txt", ios::app); // File classList chứa toàn bộ các class đã tạo (chỉ chứa tên)
	out << className << '\n';
	out.close();
}