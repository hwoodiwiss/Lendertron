#include "Customer.h"

shared_ptr<Customer> Customer::Create(string FirstName, string LastName, byte Age, double AnnualIncome)
{
	GUID AccountNumber;
	CoCreateGuid(&AccountNumber);
	return shared_ptr<Customer>(new Customer(AccountNumber, FirstName, LastName, Age, AnnualIncome));
}

std::ostream& Customer::Serialize(std::ostream& out)
{
	out << m_Id;
	out.write(m_FirstName.data(), sizeof(char) * m_FirstName.length() + 1);
	out.write(m_LastName.data(), sizeof(char) * m_LastName.length() + 1);
	out.write(reinterpret_cast<char*>(&m_Age), sizeof(byte));
	out.write(reinterpret_cast<char*>(&m_AnnualIncome), sizeof(double));
	out << m_LoanIds;
	return out;
}

std::istream& Customer::Deserialize(std::istream& in)
{	
	in >> m_Id;
	m_FirstName = InStreamToString(in);
	m_LastName = InStreamToString(in);
	in.read(reinterpret_cast<char*>(&m_Age), sizeof(byte));
	in.read(reinterpret_cast<char*>(&m_AnnualIncome), sizeof(double));
	in >> m_LoanIds;
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
