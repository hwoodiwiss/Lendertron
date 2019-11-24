#pragma once
#include "CommonIncludes.h"
#include "ISerializable.h"
#include "SerialiazablGuid.h"
#include "SerializableVector.h"

class Customer : public ISerializable
{
public:
	Customer() {}
	static Customer* Create(string FirstName, string LastName, byte Age, double AnnualIncome);

	GUID GetId() { return m_Id.AsGuid(); }
	byte GetAge() { return m_Age; }
	string GetFirstName() { return m_FirstName; }
	string GetLastName() { return m_LastName; }
	string GetFullName() { return m_FirstName + " " + m_LastName; }
	double GetIncome() { return m_AnnualIncome; }
	const vector<SerializableGuid*> GetLoanIds() { return m_LoanIds; }

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

