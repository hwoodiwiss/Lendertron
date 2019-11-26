#pragma once
#include "Common.h"
#include "LoanType.h"
#include "ISerializable.h"

class Loan : public ISerializable
{
public:
	Loan() { m_Duration = 0; m_Interest = 0; m_Value = 0; }
	Loan(GUID Id, string TypeName, int Duration, float Interest, double Value);
	void SetCustomer(GUID CustomerId);

	GUID GetId() { return m_Id.AsGuid(); }
	GUID GetCustomerId() { return m_CustomerId.AsGuid(); }
	string GetTypeName() { return m_TypeName; }
	double GetValue() { return m_Value; }
	int GetDuration() { return m_Duration; }
	string GetValueString();
	string GetDurationString();
	string GetSingleYearInterestString();
	string GetTotalInterestString();
	string GetTotalRepayableString();

	//Loan cost functions
	double GetInterestAsDecimalPercent();
	double GetSingleYearInterest();
	double GetTotalInterest();
	double GetTotalRepayable();

	//Returns a new value, or a nullptr if the desired Duration is not valid for this loan type
	static shared_ptr<Loan> NewLoan(LoanType* pLoanType, int Duration, double Value);

	//From ISerializable
	std::ostream& Serialize(std::ostream& out);
	std::istream& Deserialize(std::istream& in);

private:
	SerializableGuid m_Id;
	string m_TypeName;
	int m_Duration;
	float m_Interest;
	double m_Value;
	SerializableGuid m_CustomerId;
};

