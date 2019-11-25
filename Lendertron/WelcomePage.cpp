#include "WelcomePage.h"

WelcomePage::WelcomePage()
{
	AddPageAction(1, "Login");
	AddPageAction(2, "Exit");
}

string WelcomePage::Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser)
{
	int userChoice = 0;

	cout << "Welcome!" << endl << endl;
	cout << "This is a secure system, missuse of this system will be punished under the law!" << endl << endl;
	cout << "Please login to use the application:" << endl;
	cout << "1. Login" << endl;
	cout << "2. Exit" << endl << endl;

	userChoice = GetUserPageAction();

	return m_PageActions[userChoice];
}
