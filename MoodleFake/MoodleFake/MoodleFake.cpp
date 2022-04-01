#include <iostream>
#include "user.h"
#include "pvqn.h"

using namespace std;

int main()
{
	User* account = NULL;
	string username;
	string password;

	displaylogin(username, password);
	displaymenu(login(username, password, account));
	viewUserProfile(account);
	//changePass(account, "hello");
}
