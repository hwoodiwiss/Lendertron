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
		cout << "Please select a Customer to administrate." << endl << endl;

		ChangeCustomer(appDataManager);

	}

	while (!userExit)
	{
		if (m_CurrCustomer != nullptr)
		{
			cout << "Customer: " << m_CurrCustomer->GetLastName() << ", " << m_CurrCustomer->GetFirstName() << endl;
		}

		cout << "Customer Operations" << endl << endl;
		cout << "1. New Loan" << endl;
		cout << "2. Existing Loans" << endl;
		cout << "3. Change Customer" << endl;
		cout << "4. Back" << endl;
		cout << "5. Exit" << endl;
		userChoice = Input::GetUserInt();

		switch (userChoice)
		{
		case 1:
			NewLoan(appDataManager);
			break;
		case 2:
			ExistingLoans(appDataManager);
			break;
		case 3:
			ChangeCustomer(appDataManager);
			break;
		case 4:
			userExit = true;
			//Set context customer to nullptr
			m_CurrCustomer = nullptr;
			break;
		case 5:
			return "Exit";
		default:
			cout << "Invalid option selected, please try again." << endl;
		}
	}

	return prevPage;
}



void CustomerPage::NewLoan(shared_ptr<DataManager> appDataManager)
{
	vector<LoanType> eligbleLoans = appDataManager->GetEligbleLoanTypes(m_CurrCustomer);
	int numEligible = eligbleLoans.size();

	if (numEligible == 0)
	{
		cout << "Unfortunately, we cannot offer this customer any of our products at this time." << endl << endl;
		cout << "Press any key to return to the previous menu." << endl;
		system("pause");
		return;
	}

	LoanType selectedLoanType;
	int userSelection = 0;
	bool userCanceled = false, userLoanCreated = false;

	while (!userLoanCreated && !userCanceled)
	{
		cout << endl << "New Loan" << endl << endl;
		while (userSelection < 1 || userSelection > numEligible + 1)
		{
			cout << "These are the loan types this customer is eligible for:" << endl;
			for (int index = 0; index < numEligible; index++)
			{
				LoanType eligbleLoan = eligbleLoans[index];
				cout << index + 1 << ". " << eligbleLoan.GetName() << endl;
			}

			cout << numEligible + 1 << ". Cancel" << endl << endl;
			cout << "Please select a loan type:" << endl;
			userSelection = Input::GetUserInt();

			if (userSelection < 1 || userSelection > numEligible + 1)
			{
				cout << "Invalid selection. PLease try again." << endl;
			}
		}

		if (userSelection < numEligible + 1)
		{
			LoanType selectedType = eligbleLoans[userSelection - 1];
			if (CreateCustomerLoan(appDataManager, selectedType)) userLoanCreated = true;
		}
		else
		{
			userCanceled = true;
		}
	}
}

void CustomerPage::ExistingLoans(shared_ptr<DataManager> appDataManager)
{
	//Gets list of loans for the current in-context customer
	auto customerLoans = appDataManager->GetCustomerLoans(m_CurrCustomer->GetId().AsGuid());

	PrintLoanTable(customerLoans);
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
		cout << "3. Back" << endl << endl;

		cout << "Please select an option:" << endl;
		userChoice = Input::GetUserInt();

		switch (userChoice)
		{
		case 1:
			m_CurrCustomer = FindCustomer(appDataManager);
			if (m_CurrCustomer != nullptr) userExit = true;
			break;
		case 2:
			m_CurrCustomer = AddCustomer(appDataManager);
			if (m_CurrCustomer != nullptr) userExit = true;
			break;
		case 3:
			userExit = true;
			break;
		default:
			cout << "Invalid option selected, please try again." << endl;
		}
	}
}

bool CustomerPage::CreateCustomerLoan(shared_ptr<DataManager> appDataManager, LoanType CustLoanType)
{
	//Instantly end if the customer is nullptr, should not be able to reach this state.
	if (m_CurrCustomer == nullptr) return false;

	shared_ptr<Loan> newLoan = nullptr;

	int userDuration = 0;
	double userValue = 0.0f;
	bool userCancel = false;

	cout << "Create new " << CustLoanType.GetName() << " Loan:" << endl
		<< "Enter a negative value to cancel." << endl << endl;
	while ((userDuration < CustLoanType.GetMinDuration() || userDuration > CustLoanType.GetMaxDuration()) && !userCancel)
	{
		cout << "Please enter the desired duration in months (Min: " << CustLoanType.GetMinDuration() << " - Max: " << CustLoanType.GetMaxDuration() << "):" << endl;
		userDuration = Input::GetUserInt();
		if (userDuration < 0)
		{
			userCancel = true;
		}
		else if (userDuration < CustLoanType.GetMinDuration() || userDuration > CustLoanType.GetMaxDuration())
		{
			cout << "Entered duration is invalid for this loan type." << endl;
		}
	}

	while ((userValue < 1.0f || userValue > CustLoanType.GetMaxValue()) && !userCancel)
	{
		cout << "Please enter the desired loan amount (Max: " << CustLoanType.GetMaxValue() << "):" << endl;
		userValue = Input::GetUserFloat();
		if (userValue < 0.0f)
		{
			userCancel = true;
		}
	}

	newLoan = Loan::NewLoan(&CustLoanType, userDuration, userValue);

	if (newLoan == nullptr)
	{
		return false;
	}

	string userAccept = "";

	PrintLoanTable(vector<shared_ptr<Loan>>{newLoan});

	while ((userAccept != "y" && userAccept != "n") && !userCancel)
	{
		cout << "Please enter your decision ([Y]es / [N]o):" << endl;
		userAccept = Input::GetUserString();
		userAccept = Input::ToLower(userAccept);
		if (userAccept == "")
		{
			userCancel = true;
		}
	}

	if (userAccept == "y")
	{
		newLoan->SetCustomer(m_CurrCustomer->GetId().AsGuid());
		m_CurrCustomer->AddLoan(newLoan->GetId());
		appDataManager->AddLoan(newLoan);
		cout << "Loan has been added to this account." << endl;
		return true;
	}

	if (userAccept == "n")
	{
		cout << "Loan has not been added." << endl;
	}

	return false;
}

void CustomerPage::PrintLoanTable(std::vector<shared_ptr<Loan>> printLoans)
{

	//Print a table of the customers loans
	cout << string(118, '_') << endl;
	cout << "|" << std::left << std::setw(12) << std::setfill(' ') << "Loan";
	cout << "|" << std::left << std::setw(10) << std::setfill(' ') << "Amount";
	cout << "|" << std::left << std::setw(7) << std::setfill(' ') << "APR";
	cout << "|" << std::left << std::setw(20) << std::setfill(' ') << "Duration";
	cout << "|" << std::left << std::setw(23) << std::setfill(' ') << "Interest For One Year";
	cout << "|" << std::left << std::setw(23) << std::setfill(' ') << "Interest For Duration";
	cout << "|" << std::left << std::setw(16) << std::setfill(' ') << "Total Payable" << "|";

	for (auto currLoan : printLoans)
	{
		cout << endl << string(118, '_') << endl;
		cout << "|" << std::left << std::setw(12) << std::setfill(' ') << currLoan->GetTypeName();
		cout << "|" << std::left << std::setw(10) << std::setfill(' ') << currLoan->GetValueString();
		cout << "|" << std::left << std::setw(7) << std::setfill(' ') << currLoan->GetAprString();
		cout << "|" << std::left << std::setw(20) << std::setfill(' ') << currLoan->GetDurationString();
		cout << "|" << std::left << std::setw(23) << std::setfill(' ') << currLoan->GetSingleYearInterestString();
		cout << "|" << std::left << std::setw(23) << std::setfill(' ') << currLoan->GetTotalInterestString();
		cout << "|" << std::left << std::setw(16) << std::setfill(' ') << currLoan->GetTotalRepayableString() << "|";
	}
	cout << endl << string(118, '_') << endl << endl;
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
				cout << index + 1 << ". Acc: " << curr->GetLastName() << ", " << curr->GetFirstName() << endl;
			}
			cout << countFound + 1 << ". Not Found (Try Again)" << endl;
			cout << countFound + 2 << ". Cancel" << endl << endl;
			int userSelection = 0;
			while (userSelection < 1 || userSelection > countFound + 2)
			{
				cout << "Please select an option:" << endl;
				userSelection = Input::GetUserInt();

				if (userSelection < 1 || userSelection > countFound + 1)
				{
					cout << "Invalid selection, please try again." << endl;
				}
			}

			if (userSelection < countFound + 1)
			{
				foundCustomer = foundCustomers[userSelection - 1];
			}
			else if (userSelection == countFound + 2)
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
	//Temporary signed variable so that negative values can be excluded
	int iAge = -1;
	byte Age = 0;
	double AnnualIncome = -1.0f;
	shared_ptr<Customer> newCustomer = nullptr;

	cout << "Add Customer" << endl << endl;

	//Firstname validation loop
	while (FirstName == "")
	{
		cout << "Enter Customers First Name:" << endl;
		FirstName = Input::GetUserString();
		FirstName = Input::Trim(FirstName);
	}	
	
	//Lastname validation loop
	while (LastName == "")
	{
		cout << "Enter Customers Last Name:" << endl;
		LastName = Input::GetUserString();
		LastName = Input::Trim(LastName);
	}

	//Age validation loop
	while (iAge < 0)
	{
		cout << "Enter Customers Age:" << endl;
		iAge = Input::GetUserInt();

		if (iAge < 0)
		{
			cout << "Please enter a valid age." << endl;
		}
	}
	//Assign validated signed value to unsigned Age value
	Age = iAge;

	//Annual income validation loop
	while (AnnualIncome < 0.0f)
	{
		cout << "Enter Customers Annual Income (" << char(156) << "):" << endl;
		AnnualIncome = Input::GetUserFloat();

		if (AnnualIncome < 0.0f)
		{
			cout << "Please enter a valid annual income." << endl;
		}
	}

	//Create a new customer
	newCustomer = Customer::Create(FirstName, LastName, Age, AnnualIncome);

	//Push the new customer to the application data store
	appDataManager->AddCustomer(newCustomer);

	return newCustomer;
}
