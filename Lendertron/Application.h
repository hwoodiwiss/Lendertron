#pragma once

#include "CommonIncludes.h"
#include "Menu.h"

//Class to store the basic framework of the application, made to be overriden with the application type.
class Application
{
public:
	Application();

	void SetParams(int argc, char** argv);
	int Run();
	shared_ptr<User> GetCurrentUser() { return m_CurrentUser; }
protected:
	map<int, string> m_Params;
	map<string, string> m_Options;
	shared_ptr<User> m_CurrentUser;
	bool m_Running;
	
};