#pragma once
#include "CommonIncludes.h"

class Customer
{
public:
	static Customer* Create(string FirstName, string LastName, byte Age, double AnnualIncome);

	GUID GetId() { return m_Id; }
	byte GetAge() { return m_Age; }
	string GetFirstName() { return m_FirstName; }
	string GetLastName() { return m_LastName; }
	string GetFullName() { return m_FirstName + " " + m_LastName; }
	double GetIncome() { return m_AnnualIncome; }
	vector<GUID> GetLoanIds() { return m_LoanIds; }
private:
	Customer() {}
	Customer(GUID Id, string FirstName, string LastName, byte Age, double AnnualIncome);
	bool IsAccountNumberUnique(string AccountNumber);

	GUID m_Id;
	string m_FirstName;
	string m_LastName;
	byte m_Age;
	double m_AnnualIncome;
	vector<GUID> m_LoanIds;
};

