#pragma once
#include "Common.h"
#include "DataManager.h"
#include "PageManager.h"
#include "User.h"

class Application
{
public:
	Application();

	//Set the application parameters (Usually just the parameters to main from the runtime)
	void SetParams(int argc, char** argv);

	//Runs the main body of the application
	int Run();

private:

	//Loads data from disk into the data manager
	bool LoadDataStore();

	//Stores the data manager back to disk
	void SaveDataStore();

	//Sets up static loan type data
	void SetupLoanTypes();

	//Sets up the pages in the page manager
	void SetupPages();

	map<int, string> m_Params;
	map<string, string> m_Options;

	//Data manager is shared_ptr so that it can be passed around to other components of the application in a memory safe way
	std::shared_ptr<DataManager> m_DataManager;
	std::unique_ptr<PageManager> m_PageManager;

};