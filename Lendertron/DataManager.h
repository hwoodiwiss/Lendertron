#pragma once
#include "CommonIncludes.h"
#include "Customer.h"
#include "Loan.h"
#include "LoanType.h"

class DataManager
{
public:
	vector<Loan*> GetCustomerLoans(GUID CustomerId);
	Customer* GetLoanCustomer(GUID LoanId);

private:
	vector<Customer*> m_Customers;
	vector<Loan*> m_Loans;
};