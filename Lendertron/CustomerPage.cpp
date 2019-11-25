#include "CustomerPage.h"

CustomerPage::CustomerPage()
{
}

string CustomerPage::Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser)
{
	//Ejects users from the application if they manage to get to an authentication requiring page without logging in
	if (!IsLoggedIn(appUser))
	{
		return "Exit";
	}

	int userChoice = 0;
	bool userExit = false;

	while (m_CurrCustomer == nullptr)
	{
		ChangeCustomer(appDataManager);

		if (m_CurrCustomer == nullptr)
		{
			cout << "Please select a Customer to administrate." << endl;
		}
	}

	if (m_CurrCustomer != nullptr)
	{
		cout << "Customer:" << m_CurrCustomer->GetId().ToString() << " " << m_CurrCustomer->GetLastName() << ", " << m_CurrCustomer->GetFirstName() << endl;
	}
	while (!userExit)
	{
		cout << "Customer Operations" << endl << endl;
		cout << "1. Product Management" << endl;
		cout << "2. Change Customer" << endl;
		cout << "3. Back" << endl;
		cout << "4. Exit" << endl;
		userChoice = Input::GetUserInt();

		switch (userChoice)
		{
		case 1:
			SelectProduct(appDataManager);
			break;
		case 2:
			ChangeCustomer(appDataManager);
			break;
		case 3:
			userExit = true;
			break;
		case 4:
			return "Exit";
		default:
			cout << "Invalid option selected, please try again." << endl;
		}
	}

	return prevPage;
}



void CustomerPage::SelectProduct(shared_ptr<DataManager> appDataManager)
{
	vector<LoanType> eligbleLoans = appDataManager->GetEligbleLoanTypes(m_CurrCustomer);

}

void CustomerPage::ChangeCustomer(shared_ptr<DataManager> appDataManager)
{
	int userChoice = 0;
	bool userExit = false;

	while (!userExit)
	{
		cout << "Select Customer" << endl << endl;
		cout << "1. Search" << endl;
		cout << "2. Create New" << endl;
		cout << "3. Back" << endl;
		userChoice = Input::GetUserInt();

		switch (userChoice)
		{
		case 1:
			m_CurrCustomer = FindCustomer(appDataManager);
			break;
		case 2:
			m_CurrCustomer = AddCustomer(appDataManager);
			break;
		case 3:
			userExit = true;
			break;
		default:
			cout << "Invalid option selected, please try again." << endl;
		}
	}
}

shared_ptr<Customer> CustomerPage::FindCustomer(shared_ptr<DataManager> appDataManager)
{
	string FirstName = "";
	string LastName = "";
	shared_ptr<Customer> foundCustomer = nullptr;
	bool cancelSearch = false;

	while (foundCustomer == nullptr && !cancelSearch)
	{
		cout << "Customer Search (Leave all fields blank to cancel)" << endl << endl;
		cout << "Please enter the customers first name (or leave blank):" << endl;
		FirstName = Input::GetUserString();
		FirstName = Input::Trim(FirstName);

		cout << "Please enter the customers last name (or leave blank):" << endl;
		LastName = Input::GetUserString();
		LastName = Input::Trim(LastName);

		if (FirstName == "" && LastName == "") 
			cancelSearch = true;

		if (!cancelSearch)
		{
			vector<shared_ptr<Customer>> foundCustomers = appDataManager->SearchCustomers(FirstName, LastName);
			int countFound = foundCustomers.size();

			cout << "Select Customer:" << endl;

			for (int index = 0; index < countFound; index++)
			{
				shared_ptr<Customer> curr = foundCustomers[index];
				cout << index + 1 << ". Acc:" << curr->GetId().ToString() << " " << curr->GetLastName() << ", " << curr->GetFirstName() << endl;
			}
			cout << countFound << ". Not Found";
			cout << countFound + 1 << ". Cancel";
			int userSelection = 0;
			while (userSelection < 1 || userSelection > countFound + 1)
			{
				userSelection = Input::GetUserInt();

				if (userSelection < 1 || userSelection > countFound + 1)
				{
					cout << "Invalid selection, please try again." << endl;
				}
			}

			if (userSelection < countFound)
			{
				foundCustomer = foundCustomers[userSelection - 1];
			}
			else if (userSelection == countFound + 1)
			{
				cancelSearch = true;
			}

		}
	}

	return foundCustomer;

}

shared_ptr<Customer> CustomerPage::AddCustomer(shared_ptr<DataManager> appDataManager)
{
	string FirstName = "";
	string LastName = "";
	byte Age = 0;
	double AnnualIncome = 0.0f;
	shared_ptr<Customer> newCustomer = nullptr;

	cout << "Add Customer" << endl << endl;

	while (FirstName == "")
	{
		cout << "Enter Customers First Name:" << endl;
		FirstName = Input::GetUserString();
		FirstName = Input::Trim(FirstName);
	}	
	
	while (LastName == "")
	{
		cout << "Enter Customers Last Name:" << endl;
		LastName = Input::GetUserString();
		LastName = Input::Trim(LastName);
	}

	cout << "Enter Customers Age:" << endl;
	Age = Input::GetUserInt();

	cout << "Enter Customers Annual Income (" << char(156) << "):" << endl;
	AnnualIncome = Input::GetUserFloat();

	newCustomer = Customer::Create(FirstName, LastName, Age, AnnualIncome);

	appDataManager->AddCustomer(newCustomer);

	return newCustomer;
}
