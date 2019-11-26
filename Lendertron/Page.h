#pragma once
#include "Common.h"
#include "DataManager.h"
#include "Input.h"

using std::pair;

class Page
{
public:
	//public entrypoint to executing page, drawsbasic header and information, then runs derived page action
	string ExecutePage(string prevPage, shared_ptr<DataManager> appDataStore, shared_ptr<User>& currentUser);

protected:
	//Helper to speed up adding page actions in derived pages
	void AddPageAction(int key, string value);

	//Helper to enforce user is logged in
	bool IsLoggedIn(shared_ptr<User> currentUser);

	//Basic page option validation loop
	int GetUserPageAction();

	//Pure virtual function, derived pages must have an implementation
	virtual string Execute(string prevPage, shared_ptr<DataManager> appDataStore, shared_ptr<User>& currentUser) = 0;

	//Page action map can be optionally used by pages
	map<int, string> m_PageActions;

private:
	//Outputs the application header
	void DrawHeader();
};