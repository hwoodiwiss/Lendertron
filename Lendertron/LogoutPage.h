#pragma once
#include "Page.h"

class LogoutPage : public Page
{
public:
	LogoutPage() {};

protected:
	//Very basic page, just clears the appUser ptr and redirects to Welcome
	string Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser)
	{
		appUser = nullptr;
		return "Welcome";
	}
};