#include "user.h"

using namespace std;

//void createAcc(User* head) { //create new user
//	User* tmp = head->next;
//	head->next = new User;
//	head->next->next = tmp;
//}

void addAcc(User*& acc) {
	ofstream out;
	out.open("data/accounts.txt", ios::app);
	out << acc->username << ' ' << acc->password << ' '
		<< acc->role << ' ' << acc->Class << '\n'; //In thông tin user ra file account.txt
	out.close();
}

void getAcc(User*& acc) {
	string username, password, role, Class;
	User* u = NULL, *uCur = acc;
	ifstream fin("data/accounts.txt");
	while (fin >> username >> password >> role >> Class) {
		u = new User;
		u->username = username;
		u->password = password;
		u->role = role;
		u->Class = Class;
		u->next = NULL;
		if (acc == NULL) {
			acc = u;
			uCur = acc;
		}
		else {
			uCur->next = u;
			uCur = u;
		}
	}
	fin.close();
}

User* login(string username, string password) {
	User* acc;
	getAcc(acc);
	while (acc != NULL) {
		if (username == acc->username && password == acc->password)
			return acc;
		else acc = acc->next;
	}
	return NULL;
}

void changePass(User*& account, string newPass) {
	User* acc = NULL;
	getAcc(acc);
	
	while (acc != NULL) {
		if (acc->username == account->username) {
			account->password = newPass;
			break;
		}
		else acc = acc->next;
	}
}

