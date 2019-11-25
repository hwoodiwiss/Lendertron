#pragma once
#include "Page.h"

class MainPage : public Page
{
public:
	MainPage();

protected:
	string Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser);
};
