#include "DataManager.h"
#include <fstream>

using ifstream = std::ifstream;
using ofstream = std::ofstream;

shared_ptr<User> DataManager::FindUser(string UserName)
{
	User* FoundUser = nullptr;
	auto UserIterator = std::find_if(m_Users.begin(), m_Users.end(), [UserName](shared_ptr<User> pUser)->bool { return pUser->GetUsername() == UserName; });
	if (UserIterator == m_Users.end())
		return nullptr;

	return *UserIterator;
}

shared_ptr<Customer> DataManager::GetCustomer(GUID CustomerId)
{
	auto findIter = std::find_if(m_Customers.begin(), m_Customers.end(), [CustomerId](shared_ptr<Customer> pCust)->bool { return pCust->GetId() == CustomerId; });
	if (findIter != m_Customers.end())
	{
		return *findIter;
	}

	return nullptr;
}

shared_ptr<Loan> DataManager::GetLoan(GUID LoanId)
{
	auto findIter = std::find_if(m_Loans.begin(), m_Loans.end(), [LoanId](shared_ptr<Loan> pLoan)->bool { return pLoan->GetId() == LoanId; });
	if (findIter != m_Loans.end())
	{
		return *findIter;
	}

	return nullptr;
}

vector<LoanType> DataManager::GetEligbleLoanTypes(shared_ptr<Customer> pCustomer)
{
	vector<LoanType> EligbleTypes;
	for (auto CurrType : m_LoanTypes)
	{
		if (CurrType.IsEligible(pCustomer))
		{
			EligbleTypes.push_back(CurrType);
		}
	}

	return EligbleTypes;
}

DataManager::~DataManager()
{
	m_Loans.clear();
	m_Customers.clear();
	m_Users.clear();
}

void DataManager::Save(fs::path filePath)
{
	ofstream outStream(filePath.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
	outStream << *this;
	outStream.close();
}

void DataManager::Load(fs::path filePath)
{
	m_UpdatePath = filePath;
	ifstream inStream(filePath.c_str(), std::ios::in | std::ios::binary);
	inStream >> *this;
	inStream.close();
}

vector<shared_ptr<Customer>> DataManager::SearchCustomers(string FirstName, string LastName)
{
	//Transform the names to lowercase for easier comparison
	std::transform(FirstName.begin(), FirstName.end(), FirstName.begin(), ::tolower);
	std::transform(LastName.begin(), LastName.end(), LastName.begin(), ::tolower);

	vector<shared_ptr<Customer>> matchedCustomers;

	for (auto pCustomer : m_Customers)
	{
		string CustFName = pCustomer->GetFirstName();
		string CustLName = pCustomer->GetLastName();
		std::transform(CustFName.begin(), CustFName.end(), CustFName.begin(), ::tolower);
		std::transform(CustLName.begin(), CustLName.end(), CustLName.begin(), ::tolower);
		if (CustFName == FirstName || CustLName == LastName)
		{
			matchedCustomers.push_back(pCustomer);
		}
	}

	return matchedCustomers;
}

vector<shared_ptr<Loan>> DataManager::GetCustomerLoans(GUID CustomerId)
{
	shared_ptr<Customer> FoundCustomer = nullptr;

	//Using auto for iterators because it's much cleaner than vector<Customer>::iterator
	auto FoundCustomerIterator = std::find_if(m_Customers.begin(), m_Customers.end(), [CustomerId](shared_ptr<Customer> pCustomer)->bool { return pCustomer->GetId() == CustomerId; });
	if (FoundCustomerIterator != m_Customers.end())
	{
		FoundCustomer = *FoundCustomerIterator;
	}
	else
	{
		return vector<shared_ptr<Loan>>();
	}

	vector<shared_ptr<SerializableGuid>> CustLoanIds = FoundCustomer->GetLoanIds();

	vector<shared_ptr<Loan>> CustLoans;

	for (auto LoanId : CustLoanIds)
	{
		auto CustLoanIterator = std::find_if(m_Loans.begin(), m_Loans.end(), [LoanId](shared_ptr<Loan> pLoan)-> bool { return pLoan->GetId() == (*LoanId); });
		if (CustLoanIterator != m_Loans.end())
		{
			CustLoans.push_back(*CustLoanIterator);
		}
	}

	return CustLoans;

}

shared_ptr<Customer> DataManager::GetLoanCustomer(GUID LoanId)
{
	shared_ptr<Loan> FoundLoan = nullptr;

	auto FoundLoanIterator = std::find_if(m_Loans.begin(), m_Loans.end(), [LoanId](shared_ptr<Loan> pLoan)->bool { return pLoan->GetId() == LoanId; });
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

	auto CustIterator = std::find_if(m_Customers.begin(), m_Customers.end(), [FoundLoan](shared_ptr<Customer> pCustomer)->bool { return pCustomer->GetId() == FoundLoan->GetCustomerId(); });
	if (CustIterator == m_Customers.end())
	{
		return nullptr;
	}

	return *CustIterator;
}

void DataManager::AddUser(shared_ptr<User> pNewUser)
{
	if (pNewUser != nullptr)
		m_Users.push_back(pNewUser);

}

void DataManager::AddCustomer(shared_ptr<Customer> pNewCustomer)
{
	if (pNewCustomer != nullptr)
		m_Customers.push_back(pNewCustomer);

}

void DataManager::AddLoan(shared_ptr<Loan> pNewLoan)
{
	if (pNewLoan != nullptr)
	{
		m_Loans.push_back(pNewLoan);

		auto LoanCustomer = GetLoanCustomer(pNewLoan->GetCustomerId());
		if (LoanCustomer != nullptr)
		{
			LoanCustomer->AddLoan(pNewLoan->GetId());
		}

	}
}

void DataManager::AddLoanType(LoanType loanType)
{
	m_LoanTypes.push_back(loanType);
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

void DataManager::Update()
{
	Save(m_UpdatePath);
}
