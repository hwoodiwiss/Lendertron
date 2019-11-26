#pragma once
#include "Common.h"
#include "ILoanCriteria.h"

class LoanType
{
public:
	LoanType() {}
	LoanType(string Name, int MinDuration, int MaxDuration, float Interest, double MaxValue) : m_Name(Name), m_DurationMin(MinDuration), m_DurationMax(MaxDuration), m_Interest(Interest), m_MaxValue(MaxValue) {}

	void AddCriteria(shared_ptr<ILoanCriteria> LoanCriteria);

	string GetName() { return m_Name; }
	int GetMinDuration() { return m_DurationMin; }
	int GetMaxDuration() { return m_DurationMax; }
	float GetInterestRate() { return m_Interest; }
	double GetMaxValue() { return m_MaxValue; }

	//Returns true if the passed customer is eligible for a loan of this type, otherwise false
	bool IsEligible(shared_ptr<Customer> pCustObj);


private:
	string m_Name;
	//Minimum loan duration in months
	int m_DurationMin;
	//Maximum loan duration in months
	int m_DurationMax;
	//Interest for loans of this type
	float m_Interest;
	//Max loan value
	double m_MaxValue;
	//List of criteria that customers must meet to be eligible for a loan of this type
	//Using shared_ptr for ease of resource management
	vector<shared_ptr<ILoanCriteria>> m_Criteria;
};

