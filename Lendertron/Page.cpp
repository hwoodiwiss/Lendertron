#include "Page.h"
#include <iostream>

using std::cout;

string Page::ExecutePage(string prevPage, shared_ptr<DataManager> appDataStore, shared_ptr<User>& currentUser)
{
	system("cls");
	DrawHeader();
	if (currentUser != nullptr)
	{
		cout << "User: " << currentUser->GetUsername() << endl << "Role: " << currentUser->GetAccessLevelString() << endl;
	}
	return Execute(prevPage, appDataStore, currentUser);
}

void Page::AddPageAction(int key, string value)
{
	m_PageActions.insert(pair<int, string>(key, value));
}

bool Page::IsLoggedIn(shared_ptr<User> currentUser)
{
	if (currentUser != nullptr && currentUser->GetAccessLevel() > 0)
	{
		return true;
	}

	return false;
}

int Page::GetUserPageAction()
{
	int UserOption = INT_MIN;
	while (m_PageActions.find(UserOption) == m_PageActions.end())
	{
		cout << "Please enter an option:" << endl;
		UserOption = Input::GetUserInt();

		if (m_PageActions.find(UserOption) == m_PageActions.end())
		{
			cout << "Invalid Option!" << endl;
		}
	}

	return UserOption;
}

void Page::DrawHeader()
{
	const static string ApplicationHeader =
	R"(
               _-=-_
              /     \
             /   (=) \
            /_  o |  _\
           /  \=|=|=/  \
          /   |=|=*=|   \
         /\   |=+=|=|   /\
         |\    \|_|/    /|
        /\               /\
     __/  \             /  \__
   _   _   \    ===    /   _   _
  /     \   \__/   \__/   /     \
 /__    |                 |    __\
 |  \__/   - - - - - - -   \__/  |
   __                    _              _                         _      ___  
  / /    ___  _ __    __| |  ___  _ __ | |_  _ __   ___   _ __   / |    / _ \ 
 / /    / _ \| '_ \  / _` | / _ \| '__|| __|| '__| / _ \ | '_ \  | |   | | | |
/ /___ |  __/| | | || (_| ||  __/| |   | |_ | |   | (_) || | | | | | _ | |_| |
\____/  \___||_| |_| \__,_| \___||_|    \__||_|    \___/ |_| |_| |_|(_) \___/ 
)";
	cout << ApplicationHeader << endl;
}
