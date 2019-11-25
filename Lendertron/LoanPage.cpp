#include "LoanPage.h"

LoanPage::LoanPage()
{
	
}

string LoanPage::Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser)
{
	//Ejects users from the application if they manage to get to an authentication requiring page without logging in
	if (!IsLoggedIn(appUser))
	{
		return "Exit";
	}

	return prevPage;
}
