#include "Application.h"
#include "User.h"
#include "MenuManager.h"
#include "DataManager.h"
#include <fstream>


using ifstream = std::ifstream;
using ofstream = std::ofstream;
namespace fs = std::filesystem;

Application::Application()
{
	m_DataManager = 0;
}


void Application::SetParams(int argc, char** argv)
{
	for (int i = 0; i < argc; i++)
	{
		string fullParam = string(argv[i]);

		m_Params.insert(std::pair<int, string>(i, fullParam));

		size_t eqIndex = fullParam.find('=');

		//If there's no equals, this is just a parameter, not an option, skip to next
		if (eqIndex == -1)
		{
			continue;
		}

		string optName = fullParam.substr(0, eqIndex);

		//Specify Ui64 to surpress "Potential overflow" warning. Honestly overkill.
		string optValue = fullParam.substr(eqIndex + 1Ui64);

		m_Options.insert(std::pair<string, string>(optName, optValue));

	}
}

//Application Run takes on the role of main
int Application::Run()
{
	SetupApplication();

	//Main loop
	while (m_Running)
	{

	}

	return 0;
}

bool Application::SetupApplication()
{
	m_DataManager = std::shared_ptr<DataManager>(new DataManager());

	//Load application data from the filesystem
	std::error_code relPathError;
	auto curr = fs::current_path();
	fs::path pathDataStore = fs::absolute(fs::path(L".\\Lendertron.data"), relPathError);

	if (std::filesystem::exists(pathDataStore))
	{
		ifstream inStream(pathDataStore.c_str(), std::ios::in | std::ios::binary);
		inStream >> *m_DataManager;
		inStream.close();
	}
	else
	{
		ofstream outStream(pathDataStore.c_str(), std::ios::binary);
		outStream.close();
	}

	vector<Customer*> result = m_DataManager->SearchCustomers("Hugo", "");

	return true;
}
