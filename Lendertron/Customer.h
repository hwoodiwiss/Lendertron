#pragma once
#include "Common.h"
#include "ISerializable.h"
#include "SerialiazablGuid.h"
#include "SerializableVector.h"

class Customer : public ISerializable
{
public:
	Customer() {}
	static shared_ptr<Customer> Create(string FirstName, string LastName, byte Age, double AnnualIncome);

	SerializableGuid GetId() { return m_Id; }
	byte GetAge() { return m_Age; }
	string GetFirstName() { return m_FirstName; }
	string GetLastName() { return m_LastName; }
	string GetFullName() { return m_FirstName + " " + m_LastName; }
	double GetIncome() { return m_AnnualIncome; }
	const vector<shared_ptr<SerializableGuid>> GetLoanIds() { return m_LoanIds; }

	void AddLoan(SerializableGuid LoanId) { m_LoanIds.push_back(std::make_shared<SerializableGuid>(LoanId)); };

	std::ostream& Serialize(std::ostream& out);
	std::istream& Deserialize(std::istream& in);

private:
	Customer(GUID Id, string FirstName, string LastName, byte Age, double AnnualIncome);
	bool IsAccountNumberUnique(string AccountNumber);

	SerializableGuid m_Id;
	string m_FirstName;
	string m_LastName;
	byte m_Age;
	double m_AnnualIncome;
	SerializableVector<SerializableGuid> m_LoanIds;
};

