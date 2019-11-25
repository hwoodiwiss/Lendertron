#pragma once
#include "Page.h"

class UserPage : public Page
{
public:
	UserPage();

protected:
	string Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser);

private:
	void AddUser(shared_ptr<DataManager> appDataManager, shared_ptr<User> appUser);
	void ResetPassword(shared_ptr<DataManager> appDataManager, shared_ptr<User> appUser);
};