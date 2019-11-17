#include "Customer.h"

Customer* Customer::Create(string FirstName, string LastName, byte Age, double AnnualIncome)
{
	string AccountNumber;
	return new Customer();
}

Customer* Customer::Find(string AccountNumber, string FirstName, string LastName)
{
	return new Customer();
}

Customer::Customer(string AccountNumber, string FirstName, string LastName, byte Age, double AnnualIncome) 
	: m_AccountNumber(AccountNumber), m_FirstName(FirstName), m_LastName(LastName), m_Age(Age), m_AnnualIncome(AnnualIncome)
{
}

bool Customer::IsAccountNumberUnique(string AccountNumber)
{
	return false;
}
