#include "UserPage.h"

UserPage::UserPage()
{
}

string UserPage::Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser)
{
	//Ejects users from the application if they manage to get to an authentication requiring page without logging in
	if (!IsLoggedIn(appUser))
	{
		return "Exit";
	}

	int userChoice = 0;
	bool userExit = false;

	while (!userExit)
	{
		cout << "User Administration" << endl << endl;
		cout << "1. Reset a password" << endl;
		cout << "2. Add a new user" << endl;
		cout << "3. Back" << endl;
		cout << "4. Exit" << endl;
		userChoice = Input::GetUserInt();

		switch (userChoice)
		{
		case 1:
			ResetPassword(appDataManager, appUser);
			break;
		case 2:
			AddUser(appDataManager, appUser);
			break;
		case 3:
			userExit = true;
			break;
		case 4:
			return "Exit";
		default:
			cout << "Invalid option selected, please try again." << endl;
		}
	}
	return prevPage;
}

void UserPage::AddUser(shared_ptr<DataManager> appDataManager, shared_ptr<User> appUser)
{
	//Only allow admins to perform this function
	if (appUser->GetAccessLevel() == AL_ADMIN)
	{
		string newUsername = "";
		string newPassword = "";
		int newAccessLevel = 0;
		bool isUnique = false;

		cout << "New User" << endl << endl;

		//Uniquness validation loop
		while (!isUnique)
		{
			//Username input validation loop
			while (newUsername == "")
			{
				cout << "Please enter the new username:" << endl;
				newUsername = Input::GetUserString();
				newUsername = Input::Trim(newUsername);
			}

			//If no user is found with this username, isUnique is true
			if (appDataManager->FindUser(newUsername) == nullptr)
			{
				isUnique = true;
			}
			else
			{
				cout << "Username already in use, please try again!" << endl;
			}
		}

		//Password input validation loop
		while (newPassword == "")
		{
			cout << "Please enter the new password (User will be prompted to change this on first login):" << endl;
			newPassword = Input::GetUserString();
			newPassword = Input::Trim(newPassword);
		}

		//Access level validation loop
		while (newAccessLevel < 1 || newAccessLevel > 2)
		{
			cout << "Please enter the desired access level for this user (User = 1, Admin = 2):" << endl;
			newAccessLevel = Input::GetUserInt();
			if (newAccessLevel < 1 || newAccessLevel > 2)
			{
				cout << "Invalid value, please enter a value within the specified range." << endl;
			}
		}

		//Create a new user and add it to the data manager in one line
		appDataManager->AddUser(shared_ptr<User>(new User(newUsername, newPassword, true, (UserAccessLevel)newAccessLevel)));

		cout << "New user created!" << endl;
	}
	else
	{
		cout << "You do not have the access level required to make this change!" << endl;
	}
}

void UserPage::ResetPassword(shared_ptr<DataManager> appDataManager, shared_ptr<User> appUser)
{

	string searchUsername = "";
	shared_ptr<User> foundUser = nullptr;
	cout << "Password Reset" << endl << endl;

	while (foundUser == nullptr)
	{
		cout << "Please enter a username (or enter nothing to cancel):" << endl;
		searchUsername = Input::GetUserString();
		if (searchUsername == "")
			return;
		foundUser = appDataManager->FindUser(searchUsername);
		if (foundUser == nullptr)
		{
			cout << "No record could be found for that username!" << endl;
		}
	}

	//Does not allow the password to be reset unless by an admin, or if the selected user is the current user
	if (appUser->GetAccessLevel() == AL_ADMIN || foundUser == appUser)
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

		//Sets the new password, and forces the user to change it on next logon if the user in question is not the current user.
		foundUser->ChangePassword(newPassword, foundUser == appUser ? false : true);

		cout << "Password reset complete!" << endl;
	}
	else
	{
		cout << "You do not have permission to update this users details!" << endl;
	}
}

