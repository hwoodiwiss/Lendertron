#include "DataManager.h"

vector<Loan*> DataManager::GetCustomerLoans(GUID CustomerId)
{
	Customer* FoundCustomer = nullptr;

	//Using auto for iterators because it's much cleaner than vector<Customer*>::iterator
	auto FoundCustomerIterator = std::find_if(m_Customers.begin(), m_Customers.end(), [CustomerId](Customer* pCustomer)->bool { return pCustomer->GetId() == CustomerId; });
	if (FoundCustomerIterator != m_Customers.end())
	{
		FoundCustomer = *FoundCustomerIterator;
	}
	else
	{
		return vector<Loan*>();
	}

	vector<GUID> CustLoanIds = FoundCustomer->GetLoanIds();

	vector<Loan*> CustLoans;

	for (auto LoanId : CustLoanIds)
	{
		auto CustLoanIterator = std::find_if(m_Loans.begin(), m_Loans.end(), [LoanId](Loan* pLoan)-> bool { return pLoan->GetId() == LoanId; });
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
