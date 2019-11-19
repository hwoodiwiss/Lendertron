#pragma once

#include "CommonIncludes.h"
#include "User.h"

//Singleton application class to allow the core application object to be accessed throughout
class Application
{
public:
	Application();
	void SetParams(int argc, char** argv);
	int Run();

private:

	bool SetupApplication();

	map<int, string> m_Params;
	map<string, string> m_Options;
	bool m_Running;
	
};