#pragma once
#include "Page.h"

class LoanPage : public Page
{
public:
	LoanPage();

protected:
	string Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser);
};