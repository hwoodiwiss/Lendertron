#include "Application.h"


Application::Application()
{

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
	//Load data from disk

	//Main loop
	while (m_Running)
	{

	}

	return 0;
}
