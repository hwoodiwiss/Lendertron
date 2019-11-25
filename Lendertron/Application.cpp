#include "Application.h"
#include "User.h"
#include "DataManager.h"

//LoanTypeCriteria Types
#include "FinanceCriteria.h"
#include "AgeCriteria.h"

//Application Page Types
#include "WelcomePage.h"
#include "LoginPage.h"
#include "MainPage.h"
#include "LogoutPage.h"
#include "CustomerPage.h"
#include "LoanPage.h"
#include "UserPage.h"

#include <fstream>




using ifstream = std::ifstream;
using ofstream = std::ofstream;
using std::cout;
using std::cin;
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
	m_DataManager = shared_ptr<DataManager>(new DataManager());
	m_PageManager = unique_ptr<PageManager>(new PageManager());
	shared_ptr<User> appUser = nullptr;

	//Loads data from disk into DataManager
	if (!LoadDataStore() || m_DataManager->FindUser("Administrator") == nullptr)
	{
		//If there was no data store found, add default user, with default password
		auto DefaultUser = shared_ptr<User>(new User("Administrator", "admin", true, UserAccessLevel::AL_ADMIN));
		m_DataManager->AddUser(DefaultUser);
	}

	//Setup loan types. (Statically defined in code)
	SetupLoanTypes();

	//Setup application pages
	SetupPages();

	shared_ptr<Page> currPageObj = m_PageManager->GetPage("Welcome");
	string nextPage;
	string prevPage = "";
	while (currPageObj != nullptr)
	{
		string prevNextPage = nextPage;
		nextPage = currPageObj->ExecutePage(prevPage, m_DataManager, appUser);
		prevPage = prevNextPage;
		currPageObj = m_PageManager->GetPage(nextPage);
	}

	SaveDataStore();

	return 0;
}

bool Application::LoadDataStore()
{
	//Load application data from the filesystem
	std::error_code relPathError;
	auto curr = fs::current_path();
	fs::path pathDataStore = fs::absolute(fs::path(L".\\Lendertron.data"), relPathError);

	if (std::filesystem::exists(pathDataStore))
	{
		m_DataManager->Load(pathDataStore);
	}
	else
	{
		//Create default empty file if it doesn't exist
		ofstream outStream(pathDataStore.c_str(), std::ios::binary);
		outStream.close();
		return false;
	}

	return true;
}

void Application::SaveDataStore()
{
	//Load application data from the filesystem
	std::error_code relPathError;
	auto curr = fs::current_path();
	fs::path pathDataStore = fs::absolute(fs::path(L".\\Lendertron.data"), relPathError);

	m_DataManager->Save(pathDataStore);
}

void Application::SetupLoanTypes()
{
	//Setup Long Term loan type
	shared_ptr<ILoanCriteria> LongTermAgeCriteria = shared_ptr<ILoanCriteria>(new AgeCriteria(21));
	shared_ptr<ILoanCriteria> LongTermFinanceCriteria = shared_ptr<ILoanCriteria>(new FinanceCriteria(24000.00f));
	LoanType LongTermLoan = LoanType("Long Term", (3 * 12), (5 * 12), 4.9f, 40000.00f);
	LongTermLoan.AddCriteria(LongTermAgeCriteria);
	LongTermLoan.AddCriteria(LongTermFinanceCriteria);
	
	//Setup Short Term loan type
	shared_ptr<ILoanCriteria> ShortTermAgeCriteria = shared_ptr<ILoanCriteria>(new AgeCriteria(18));
	shared_ptr<ILoanCriteria> ShortTermFinanceCriteria = shared_ptr<ILoanCriteria>(new FinanceCriteria(21000.00f));
	LoanType ShortTermLoan = LoanType("Short Term", (1 * 12), (2 * 12), 3.9f, 12000.00f);
	ShortTermLoan.AddCriteria(ShortTermAgeCriteria);
	ShortTermLoan.AddCriteria(ShortTermFinanceCriteria);

	//Setup Short Term loan type
	shared_ptr<ILoanCriteria> EmergencyAgeCriteria = shared_ptr<ILoanCriteria>(new AgeCriteria(18));
	shared_ptr<ILoanCriteria> EmergencyFinanceCriteria = shared_ptr<ILoanCriteria>(new FinanceCriteria(12000.00f));
	LoanType EmergencyLoan = LoanType("Emergency", 1, 6, 29.9f, 3000.00f);
	EmergencyLoan.AddCriteria(EmergencyAgeCriteria);
	EmergencyLoan.AddCriteria(EmergencyFinanceCriteria);

	m_DataManager->AddLoanType(LongTermLoan);
	m_DataManager->AddLoanType(ShortTermLoan);
	m_DataManager->AddLoanType(EmergencyLoan);
}

void Application::SetupPages()
{
	m_PageManager->AddPage("Welcome", shared_ptr<Page>(new WelcomePage()));
	m_PageManager->AddPage("Login", shared_ptr<Page>(new LoginPage()));
	m_PageManager->AddPage("Logout", shared_ptr<Page>(new LogoutPage()));
	m_PageManager->AddPage("Main", shared_ptr<Page>(new MainPage()));
	m_PageManager->AddPage("User", shared_ptr<Page>(new UserPage()));
	m_PageManager->AddPage("Customer", shared_ptr<Page>(new CustomerPage()));
	m_PageManager->AddPage("Loan", shared_ptr<Page>(new LoanPage()));
}
