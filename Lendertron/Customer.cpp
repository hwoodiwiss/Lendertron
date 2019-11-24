#include "Customer.h"

Customer* Customer::Create(string FirstName, string LastName, byte Age, double AnnualIncome)
{
	GUID AccountNumber;
	CoCreateGuid(&AccountNumber);
	return new Customer(AccountNumber, FirstName, LastName, Age, AnnualIncome);
}

std::ostream& Customer::Serialize(std::ostream& out)
{
	out << m_Id << m_FirstName << m_LastName << m_Age << m_AnnualIncome << m_LoanIds;
	return out;
}

std::istream& Customer::Deserialize(std::istream& in)
{	
	in >> m_Id >> m_FirstName >> m_LastName >> m_Age >> m_AnnualIncome >> m_LoanIds;
	return in;
}

Customer::Customer(GUID Id, string FirstName, string LastName, byte Age, double AnnualIncome)
	: m_Id(SerializableGuid(Id)), m_FirstName(FirstName), m_LastName(LastName), m_Age(Age), m_AnnualIncome(AnnualIncome)
{
}

bool Customer::IsAccountNumberUnique(string AccountNumber)
{
	return false;
}
