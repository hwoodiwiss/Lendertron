#pragma once
#include "Page.h"

class WelcomePage : public Page
{
public:
	WelcomePage();

protected:
	string Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser);
};