#include "DataManager.h"

User* DataManager::FindUser(string UserName)
{
	User* FoundUser = nullptr;
	auto UserIterator = std::find_if(m_Users.begin(), m_Users.end(), [UserName](User* pUser)->bool { return pUser->GetUsername() == UserName; });
	if (UserIterator == m_Users.end())
		return nullptr;

	return *UserIterator;
}

vector<Customer*> DataManager::SearchCustomers(string FirstName, string LastName)
{
	//Transform the names to lowercase for easier comparison
	std::transform(FirstName.begin(), FirstName.end(), FirstName.begin(), ::tolower);
	std::transform(LastName.begin(), LastName.end(), LastName.begin(), ::tolower);

	vector<Customer*> matchedCustomers;
	auto pMatchedCustomers = &matchedCustomers;
	std::for_each(m_Customers.begin(), m_Customers.end(), [FirstName, LastName, pMatchedCustomers](Customer* pCustomer)->void {
		string CustFName = string(pCustomer->GetFirstName());
		string CustLName = string(pCustomer->GetLastName());
		std::transform(CustFName.begin(), CustFName.end(), CustFName.begin(), ::tolower);
		std::transform(CustLName.begin(), CustLName.end(), CustLName.begin(), ::tolower);
		if (CustFName == FirstName || CustLName == LastName)
		{
			pMatchedCustomers->push_back(pCustomer);
		}
	});

	return matchedCustomers;
}

vector<Loan*> DataManager::GetCustomerLoans(GUID CustomerId)
{
	Customer* FoundCustomer = nullptr;

	//Using auto for iterators because it's much cleaner than vector<Customer>::iterator
	auto FoundCustomerIterator = std::find_if(m_Customers.begin(), m_Customers.end(), [CustomerId](Customer* pCustomer)->bool { return pCustomer->GetId() == CustomerId; });
	if (FoundCustomerIterator != m_Customers.end())
	{
		FoundCustomer = *FoundCustomerIterator;
	}
	else
	{
		return vector<Loan*>();
	}

	vector<SerializableGuid*> CustLoanIds = FoundCustomer->GetLoanIds();

	vector<Loan*> CustLoans;

	for (auto LoanId : CustLoanIds)
	{
		auto CustLoanIterator = std::find_if(m_Loans.begin(), m_Loans.end(), [LoanId](Loan* pLoan)-> bool { return pLoan->GetId() == (*LoanId); });
		if (CustLoanIterator != m_Loans.end())
		{
			CustLoans.push_back(*CustLoanIterator);
		}
	}

	return CustLoans;

}

Customer* DataManager::GetLoanCustomer(GUID LoanId)
{
	Loan* FoundLoan = nullptr;

	auto FoundLoanIterator = std::find_if(m_Loans.begin(), m_Loans.end(), [LoanId](Loan* pLoan)->bool { return pLoan->GetId() == LoanId; });
	if (FoundLoanIterator != m_Loans.end())
	{
		FoundLoan = *FoundLoanIterator;
	}
	else
	{
		return nullptr;
	}

	if (FoundLoan->GetCustomerId() == GUID_NULL)
	{
		return nullptr;
	}

	auto CustIterator = std::find_if(m_Customers.begin(), m_Customers.end(), [FoundLoan](Customer* pCustomer)->bool { return pCustomer->GetId() == FoundLoan->GetCustomerId(); });
	if (CustIterator == m_Customers.end())
	{
		return nullptr;
	}

	return *CustIterator;
}

void DataManager::AddCustomer(Customer* pNewCustomerObj)
{
	if (pNewCustomerObj != nullptr)
		m_Customers.push_back(pNewCustomerObj);
}

std::ostream& DataManager::Serialize(std::ostream& os)
{
	os << m_Loans << m_Customers << m_Users;
	return os;
}

std::istream& DataManager::Deserialize(std::istream& is)
{
	is >> m_Loans >> m_Customers >> m_Users;
	return is;
}
