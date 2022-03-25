#pragma once
#include "struct.h"
using namespace std;
void addAcc(User*& acc);
void getAcc(User*& acc);
bool login(string username, string password);
void changePass(User*& account, string newPass);

