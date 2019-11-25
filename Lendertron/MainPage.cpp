#include "MainPage.h"

MainPage::MainPage()
{
	AddPageAction(1, "Customer");
	AddPageAction(2, "User");
	AddPageAction(3, "Logout");
	AddPageAction(4, "Exit");
	
}

string MainPage::Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser)
{
	int UserOption = 0;

	//Ejects users from the application if they manage to get to an authentication requiring page without logging in
	if (!IsLoggedIn(appUser))
	{
		return "Exit";
	}

	cout << "Main Menu" << endl << endl;
	cout << "Please select a function:" << endl;
	cout << "1. Customer Operations" << endl;
	cout << "2. User Administration" << endl;
	cout << "3. Logout" << endl;
	cout << "4. Exit" << endl;

	UserOption = GetUserPageAction();

	return m_PageActions[UserOption];
}
