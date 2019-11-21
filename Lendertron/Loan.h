#pragma once
#include "CommonIncludes.h"
#include "LoanType.h"

class Loan
{
public:
	Loan(GUID Id, string TypeName, int Duration, float Interest, double Value);
	void SetCustomer(GUID CustomerId);

	GUID GetId() { return m_Id; }
	GUID GetCustomerId() { return m_CustomerId; }

	//Returns a new value, or a nullptr if the desired Duration is not valid for this loan type
	static Loan* NewLoan(LoanType* pLoanType, int Duration, double Value);

private:
	GUID m_Id;
	string m_TypeName;
	int m_Duration;
	float m_Interest;
	double m_Value;
	GUID m_CustomerId;
};

