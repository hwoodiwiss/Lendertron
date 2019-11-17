#pragma once
#include "CommonIncludes.h"

class Customer
{
public:
	static Customer* Create(string FirstName, string LastName, byte Age, double AnnualIncome);
	static Customer* Find(string AccountNumber, string FirstName, string LastName);

private:
	Customer(string AccountNumber, string FirstName, string LastName, byte Age, double AnnualIncome);
	bool IsAccountNumberUnique(string AccountNumber);

	string m_AccountNumber;
	string m_FirstName;
	string m_LastName;
	byte m_Age;
	double m_AnnualIncome;
};

