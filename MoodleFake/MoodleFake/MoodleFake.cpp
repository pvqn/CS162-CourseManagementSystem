#include <iostream>
#include "user.h"
#include "pvqn.h"
#include "staff.h"

using namespace std;

int main()
{
	User* account = NULL;
	Class* classes = NULL;
	string username;
	string password;

	displaylogin(username, password);
	displaymenu(login(username, password, account));
	//viewUserProfile(account);
	//changePass(account);
	staffChoice(account, classes);
}
