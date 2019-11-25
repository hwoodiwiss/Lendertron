#pragma once
#include "Common.h"
#include "DataManager.h"
#include "Input.h"

using std::pair;

class Page
{
public:
	string ExecutePage(string prevPage, shared_ptr<DataManager> appDataStore, shared_ptr<User>& currentUser);

protected:
	//Helper to speed up adding page actions in derived pages
	void AddPageAction(int key, string value);

	//Helper to enforce user is logged in
	bool IsLoggedIn(shared_ptr<User> currentUser);

	int GetUserPageAction();

	virtual string Execute(string prevPage, shared_ptr<DataManager> appDataStore, shared_ptr<User>& currentUser) = 0;

	map<int, string> m_PageActions;

private:
	void DrawHeader();
};