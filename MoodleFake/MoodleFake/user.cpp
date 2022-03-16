#include "user.h"
#include <iostream>
#include <fstream>

using namespace std;

//void createAcc(User* head) { //create new user
//	User* tmp = head->next;
//	head->next = new User;
//	head->next->next = tmp;
//}

void addAcc(User acc) {
	ofstream out;
	out.open("data/accounts.txt", ios::app);
	out << acc.username << ' ' << acc.password << ' '
		<< acc.role << ' ' << acc.Class << '\n'; //In thông tin user ra file account.txt
	out.close();
}