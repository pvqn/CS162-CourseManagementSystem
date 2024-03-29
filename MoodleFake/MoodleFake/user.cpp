﻿#include "user.h"

using namespace std;

void addAcc(User*& acc) {
	ofstream out;
	out.open("data/accounts.txt", ios::app);
	out << acc->username << ' ' << acc->password << ' '
		<< acc->role << ' ' << acc->Class << '\n'; //In thông tin user ra file account.txt
	out.close();
}

void resetAcc(User* acc) { // Ghi lại toàn bộ acc vào file account.txt
	ofstream out("data/accounts.txt");
	while (acc != NULL) {
		out << acc->username << ' ' << acc->password << ' '
			<< acc->role << ' ' << acc->Class << '\n';  //In thông tin user ra file account.txt
		acc = acc->next;
	}
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
			uCur = uCur->next;
		}
	}
	fin.close();
}

bool checkUserExist(string username, string password) {
	// Exist: true
	// Does't exist: false
	User* acc = NULL;
	getAcc(acc);
	while (acc != NULL) {
		if (username == acc->username && password == acc->password) {
			return true;
			break;
		}
		else acc = acc->next;
	}
	return false;
}

int login(string username, string password, User*& account) {
	// Staff: 0
	// Student: 1
	// error: 2
	User* acc = NULL;
	getAcc(acc);
	while (acc != NULL) {
		if (username.find("@staff") != string::npos
			&& username == acc->username && password == acc->password) {  //Account of staff
			account = acc;
			ofstream out("data/cache/currentUser.txt");
			out << username << " ";
			out << password;
			out.close();
			return 0;
			break;
		}
		else if (username == acc->username && password == acc->password) {
			account = acc;
			ofstream out("data/cache/currentUser.txt");
			out << username << " ";
			out << password;
			out.close();
			return 1;
			break;
		}
		else acc = acc->next;
	}
	return 2;
}

void changePass(User* account) {
	User* acc = NULL;
	getAcc(acc);
	User* reset = acc;

	string newPass;
	cout << "Input your new password: ";
	cin >> newPass;
	
	while (acc != NULL) {
		if (acc->username == account->username) {
			acc->password = newPass;
			ofstream out("data/cache/currentUser.txt");
			out << acc->username << " ";
			out << newPass;
			out.close();
			break;
		}
		else acc = acc->next;
	}
	resetAcc(reset);
	cout << "Action Success!\n";
	delete reset;
}

void viewUserProfile(User*& account) {
	User* acc = NULL;
	getAcc(acc);

	while (acc != NULL) {
		if (acc->username == account->username) {
			cout << endl << "Username: " << acc->username ;
			cout << endl << "Password: ";
			for (int i = 0; i < account->password.length(); i++) {
				cout << '*';
			}
			cout << endl << "Role: " << acc->role;
			cout << endl << "Class: " << acc->Class;
			break;
		}
		else acc = acc->next;
	}
}

