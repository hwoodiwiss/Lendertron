#include "Customer.h"

Customer* Customer::Create(string FirstName, string LastName, byte Age, double AnnualIncome)
{
	GUID AccountNumber;
	CoCreateGuid(&AccountNumber);
	return new Customer(AccountNumber, FirstName, LastName, Age, AnnualIncome);
}

Customer::Customer(GUID Id, string FirstName, string LastName, byte Age, double AnnualIncome) 
	: m_Id(Id), m_FirstName(FirstName), m_LastName(LastName), m_Age(Age), m_AnnualIncome(AnnualIncome)
{
}

bool Customer::IsAccountNumberUnique(string AccountNumber)
{
	return false;
}
