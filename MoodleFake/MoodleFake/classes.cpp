#include "struct.h"
#include <direct.h>

using namespace std;

void createClass(string className) {
	string path = "data/classes/" + className; // Tạo file class, trong class chứa info học sinh của class đó
	_mkdir(path.c_str()); // Tạo thư mục theo đường dẫn path
	ofstream out;
	out.open("data/classes/classList.txt", ios::app); // File classList chứa toàn bộ các class đã tạo (chỉ chứa tên)
	out << className << '\n';
	out.close();
}