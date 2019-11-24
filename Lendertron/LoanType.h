#pragma once
#include "CommonIncludes.h"
#include "ILoanCriteria.h"

class LoanType
{
public:
	string GetName() { return m_Name; }
	int GetMinDuration() { return m_DurationMin; }
	int GetMaxDuration() { return m_DurationMax; }
	float GetInterestRate() { return m_Interest; }

	//Returns true if the passed customer is eligible for a loan of this type, otherwise false
	bool IsEligible(Customer* pCustObj);


private:
	string m_Name;
	//Minimum loan duration in months
	int m_DurationMin;
	//Maximum loan duration in months
	int m_DurationMax;
	//Interest for loans of this type
	float m_Interest;
	//List of criteria that customers must meet to be eligible for a loan of this type
	vector<ILoanCriteria*> m_Criteria;
};

