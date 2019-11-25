#pragma once
#include "Page.h"

class LoginPage : public Page
{
public:
	LoginPage();

protected:
	string Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser);
};