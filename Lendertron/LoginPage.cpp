#include "LoginPage.h"

LoginPage::LoginPage()
{

}

string LoginPage::Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser)
{
	string Username;
	string Password;
	int count = 0;

	while (count < 3)
	{
		count++;
		cout << "Please enter your username (Attempt " << count << " of 3):" << endl;
		Username = Input::GetUserString();
		cout << "Password: " << endl;
		Password = Input::GetUserString();

		//Get found user from the DataManager
		shared_ptr<User> foundUser = appDataManager->FindUser(Username);

		//If found user is nullptr of the password doesn't match, continue the loop
		if (foundUser != nullptr && foundUser->GetPassword() == Password)
		{
			cout << "Login successful!" << endl;
			if (foundUser->IsFirstLogin())
			{
				string newPassword = "";
				string newPasswordVerify = "";
				do
				{
					cout << "Please enter a new password: " << endl;
					newPassword = Input::GetUserString();
					cout << "Please reenter the new password: " << endl;
					newPasswordVerify = Input::GetUserString();

					if (newPassword != newPasswordVerify)
					{
						cout << "Passwords did not match!" << endl;
					}
				} while (newPassword != newPasswordVerify);

				foundUser->ChangePassword(newPassword);
			}

			appUser = foundUser;
			return "Main";
		}

		cout << endl << "Provided Username or Password is incorrect!" << endl;
	}

	return "Exit";
}