#pragma once

#include "CommonIncludes.h"

//Singleton application class to allow the core application object to be accessed throughout
class Application
{
public:
	Application();
	void SetParams(int argc, char** argv);
	int Run();
	shared_ptr<User> GetCurrentUser() { return m_CurrentUser; }

private:

	map<int, string> m_Params;
	map<string, string> m_Options;
	shared_ptr<User> m_CurrentUser;
	bool m_Running;
	
};