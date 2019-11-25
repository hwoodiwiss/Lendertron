#pragma once
#include "Common.h"
#include "DataManager.h"
#include "PageManager.h"
#include "User.h"

class Application
{
public:
	Application();
	void SetParams(int argc, char** argv);
	int Run();

private:

	bool LoadDataStore();
	void SaveDataStore();
	void SetupLoanTypes();
	void SetupPages();

	map<int, string> m_Params;
	map<string, string> m_Options;
	std::shared_ptr<DataManager> m_DataManager;
	std::unique_ptr<PageManager> m_PageManager;

};