#pragma once
#include "struct.h"
using namespace std;
void addAcc(User*& acc);
void getAcc(User*& acc);
void resetAcc(User* acc);
bool login(string username, string password, User*& account);
void changePass(User*& account, string newPass);
void viewUserProfile(User*& account);

